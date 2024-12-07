#include "OTBox.h"

namespace octree
{
    bool OTBox::contains(OTBox& other)
    {
        return  
            getMaxEdge().x() >= other.getMaxEdge().x() &&
            getMaxEdge().y() >= other.getMaxEdge().y() &&
            getMaxEdge().z() >= other.getMaxEdge().z() &&
            getMinEdge().x() <= other.getMinEdge().x() &&
            getMinEdge().y() <= other.getMinEdge().y() &&
            getMinEdge().z() <= other.getMinEdge().z();
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
    
    void OTBox::draw(ofColor color)
    {
        ofMaterial material;
        ofBoxPrimitive primitive;

        primitive.setPosition(position);
        primitive.setWidth(extent.x());
        primitive.setHeight(extent.y());
        primitive.setDepth(extent.z());
        primitive.setResolution(1);

        material.setDiffuseColor(color);

        material.begin();
        primitive.drawWireframe();
        material.end();
    }
}

