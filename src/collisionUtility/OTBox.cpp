#include "OTBox.h"

namespace octree
{
    bool OTBox::contains(OTBox& other)
    {
        return  getMaxEdge().x() >= other.getMaxEdge().x() &&
            getMaxEdge().y() >= other.getMaxEdge().y() &&
            getMaxEdge().z() >= other.getMaxEdge().z() &&
            getMinEdge().x() <= other.getMaxEdge().x() &&
            getMinEdge().y() <= other.getMaxEdge().y() &&
            getMinEdge().z() <= other.getMaxEdge().z();
    }

    bool OTBox::intersects(OTBox& other)
    {
        return
            !(
                getMaxEdge().x() <= other.getMinEdge().x() ||
                getMaxEdge().y() <= other.getMinEdge().y() ||
                getMaxEdge().z() <= other.getMinEdge().z() ||
                getMinEdge().x() >= other.getMaxEdge().x() ||
                getMinEdge().y() >= other.getMaxEdge().y() ||
                getMinEdge().z() >= other.getMaxEdge().z()
              );
    }
}

