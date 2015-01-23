//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef FRAMEBLOCK_H_
#define FRAMEBLOCK_H_
#include <omnetpp.h>
#include "inet/linklayer/ieee80211/mac/Ieee80211Frame_m.h"

namespace inet {
namespace ieee80211 {


class Ieee80211MpduA : public Ieee80211DataOrMgmtFrame
{
private:
    struct ShareStruct{
        Ieee80211DataOrMgmtFrame * pkt;
        unsigned int shareCount;
        int numRetries = 0;
        ShareStruct(){
            pkt=nullptr;
            shareCount = 0;
            numRetries = 0;
        }
    };
    std::vector<ShareStruct*> encapsulateVector;
    void _deleteEncapVector();
    bool _checkIfShare();
    void _detachShareVector(unsigned int i);
public:
    Ieee80211MpduA(const char *name=nullptr, int kind=0);
    Ieee80211MpduA(Ieee80211MpduA &);
    Ieee80211MpduA(Ieee80211DataOrMgmtFrame *);
    virtual Ieee80211MpduA * dup(){return new Ieee80211MpduA(*this);}
    virtual ~Ieee80211MpduA();
    Ieee80211MpduA& operator=(const Ieee80211MpduA& msg);
    virtual Ieee80211DataOrMgmtFrame *getPacket(unsigned int i) const;
    virtual int getNumRetries(unsigned int i) const;

    virtual void setPacketKind(unsigned int i,int kind);
    virtual unsigned int getNumEncap() const {return encapsulateVector.size();}
    uint64_t getPktLength(unsigned int i) const
    {
        if (i<encapsulateVector.size())
            return encapsulateVector[i]->pkt->getBitLength();
        return 0;
    }

    Ieee80211DataOrMgmtFrame *decapsulatePacket(unsigned int i);
    virtual unsigned int getEncapSize() {return encapsulateVector.size();}

    virtual void pushFront(Ieee80211DataOrMgmtFrame *);
    virtual void pushBack(Ieee80211DataOrMgmtFrame *);

    virtual void pushFront(Ieee80211DataOrMgmtFrame *,int);
    virtual void pushBack(Ieee80211DataOrMgmtFrame *,int);

    virtual Ieee80211DataOrMgmtFrame *popFront();
    virtual Ieee80211DataOrMgmtFrame *popBack();
    virtual bool haveBlock(){return !encapsulateVector.empty();}
    virtual void forEachChild(cVisitor *v);

    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);


    virtual void encapsulate(cPacket *packet)
    {
        opp_error("operation not supported");
    }


    virtual cPacket *decapsulate()
    {
        opp_error("operation not supported");
        return nullptr;
    }

    /**
     * Returns a pointer to the encapsulated packet, or nullptr if there
     * is no encapsulated packet.
     *
     * IMPORTANT: see notes at encapsulate() about reference counting
     * of encapsulated packets.
     */
    virtual cPacket *getEncapsulatedPacket() const
    {
        opp_error("operation not supported");
        return nullptr;
    }


    /**
     * Returns true if the packet contains an encapsulated packet, and false
     * otherwise. This method is potentially more efficient than
     * <tt>getEncapsulatedPacket()!=nullptr</tt>, because it does not need to
     * unshare a shared encapsulated packet (see note at encapsulate()).
     */
    virtual bool hasEncapsulatedPacket() const
    {
        opp_error("operation not supported");
        return false;
    }
};



inline void doPacking(cCommBuffer *b, Ieee80211MpduA& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, Ieee80211MpduA& obj) {obj.parsimUnpack(b);}

}
}

#endif /* FRAMEBLOCK_H_ */
