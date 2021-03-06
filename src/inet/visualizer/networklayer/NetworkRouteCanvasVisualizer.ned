//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package inet.visualizer.networklayer;

import inet.visualizer.base.PathVisualizerBase;
import inet.visualizer.contract.INetworkRouteVisualizer;

//
// This module visualizes network routes on a 2D canvas. It displays an
// polyline arrow for each active route in the network. See the documentation of
// the base module for what constitutes an active route. The arrow points from
// the source towards the destination. If a link is used in both directions then
// there are arrowheads on both ends of the arrow. Each polyline fades out over
// time until the route becomes inactive unless it is reinforced by another
// packet. The polyline automatically follows the movement of mobile nodes.
//
// @see ~NetworkRouteOsgVisualizer, ~NetworkRouteVisualizer, ~PathVisualizerBase, ~INetworkRouteVisualizer
//
simple NetworkRouteCanvasVisualizer extends PathVisualizerBase like INetworkRouteVisualizer
{
    parameters:
        double zIndex = default(3); // determines the drawing order of figures relative to other visualizers
        @class(NetworkRouteCanvasVisualizer);
}
