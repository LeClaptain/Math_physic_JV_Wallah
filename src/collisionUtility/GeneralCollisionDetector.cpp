#include "GeneralCollisionDetector.h"

GeneralCollisionDetector::GeneralCollisionDetector(maths::vec3 octreePosition, maths::vec3 octreeExtent)
{
    octree = new octree::Octree(octree::OTBox(octreePosition, octreeExtent));
    /*for (int i = 0; i < 100; i++)
    {
        auto position = maths::vec3((std::rand() % 1000) - 500, (std::rand() % 1000) - 500, (std::rand() % 1000) - 500);
        
        octree->add(new BoundingVolume(5.0f, position));
    }*/
}

void GeneralCollisionDetector::draw()
{
    if(debug)
    {
        octree->draw();
    }
}

std::vector<CollisionPair> GeneralCollisionDetector::DetectAllCollisions()
{
    collisionPairs = std::vector<CollisionPair>();
    if (!volumes)
    {
        std::cout << "volumes is nullptr, therefore everything that follows is baaaad" << std::endl;
    }
    for (auto volume = volumes->begin(); volume != volumes->end(); volume++)// for (auto& volume : volumes)
    {
        detectCollisionForOneBoundingVolume(*volume);
    }
    return collisionPairs;
}

void GeneralCollisionDetector::detectCollisionForOneBoundingVolume(BoundingVolume* volume)
{
    std::vector<BoundingVolume*> potentialColliders = octreeComputation(volume);
    if (potentialColliders.size() <= 1){return;}

    for (auto potentialCollider = potentialColliders.begin(); potentialCollider != potentialColliders.end(); volume++) // for (auto& potentialCollider : potentialColliders)
    {
        if (*potentialCollider == volume){continue;}
        if (doBoundingVolumesCollide(volume, *potentialCollider))
        {
            checkCollision(volume, *potentialCollider);
        }
    }
}


std::vector<BoundingVolume*> GeneralCollisionDetector::octreeComputation(BoundingVolume* volume)
{
    float radius = volume->getRadius();
    vec3 position = volume->getCenter();
    octree::OTBox queryBox(position, vec3(radius)); // erreur, si queryBox est trop petite on loupe des collisions potentielles
    std::vector<BoundingVolume*> potentialCollisions = octree->query(queryBox);
    return potentialCollisions;
}

bool GeneralCollisionDetector::doBoundingVolumesCollide(BoundingVolume* volume1, BoundingVolume* volume2)
{
    if (volume1->getCenter().distance(volume2->getCenter()) < volume1->getRadius() + volume2->getRadius())
    {
        return true;
    }
    return false;
}

void GeneralCollisionDetector::checkCollision(BoundingVolume* volume1, BoundingVolume* volume2)
{
    auto v1Center = volume1->getCenter();
    auto v1Extent = volume1->getRigidBody()->getExtent();
    auto v1Orientation = volume1->getRigidBody()->getOrientation().toMat3();

    auto v2Center = volume2->getCenter();
    auto v2Extent = volume2->getRigidBody()->getExtent();
    auto v2Orientation = volume2->getRigidBody()->getOrientation().toMat3();

    maths::vec3 rightTopFront_vertex(v2Center.x() + v2Extent.x(), v2Center.y() + v2Extent.y(), v2Center.y() + v2Extent.y());
    maths::vec3 leftBottomBack_vertex(v2Center.x() - v2Extent.x(), v2Center.y() - v2Extent.y(), v2Center.y() - v2Extent.y());
    rightTopFront_vertex = v2Orientation * rightTopFront_vertex;
    leftBottomBack_vertex = v2Orientation * leftBottomBack_vertex;

    std::vector<Face> faces;
    faces.push_back({ rightTopFront_vertex, v2Orientation * maths::vec3(1, 0, 0) });
    faces.push_back({ rightTopFront_vertex, v2Orientation * maths::vec3(0, 1, 0) });
    faces.push_back({ rightTopFront_vertex, v2Orientation * maths::vec3(0, 0, 1) });
    faces.push_back({ leftBottomBack_vertex, v2Orientation * maths::vec3(-1, 0, 0) });
    faces.push_back({ leftBottomBack_vertex, v2Orientation * maths::vec3(0, -1, 0) });
    faces.push_back({ leftBottomBack_vertex, v2Orientation * maths::vec3(0, 0, -1) });

    std::vector<maths::vec3> vertices;
    vertices.push_back(v1Orientation * maths::vec3(v1Center.x() + v1Extent.x(), v1Center.y() + v1Extent.y(), v1Center.z() + v1Extent.z()));
    vertices.push_back(v1Orientation * maths::vec3(v1Center.x() + v1Extent.x(), v1Center.y() + v1Extent.y(), v1Center.z() - v1Extent.z()));
    vertices.push_back(v1Orientation * maths::vec3(v1Center.x() + v1Extent.x(), v1Center.y() - v1Extent.y(), v1Center.z() + v1Extent.z()));
    vertices.push_back(v1Orientation * maths::vec3(v1Center.x() + v1Extent.x(), v1Center.y() - v1Extent.y(), v1Center.z() - v1Extent.z()));
    vertices.push_back(v1Orientation * maths::vec3(v1Center.x() - v1Extent.x(), v1Center.y() + v1Extent.y(), v1Center.z() + v1Extent.z()));
    vertices.push_back(v1Orientation * maths::vec3(v1Center.x() - v1Extent.x(), v1Center.y() + v1Extent.y(), v1Center.z() - v1Extent.z()));
    vertices.push_back(v1Orientation * maths::vec3(v1Center.x() - v1Extent.x(), v1Center.y() - v1Extent.y(), v1Center.z() + v1Extent.z()));
    vertices.push_back(v1Orientation * maths::vec3(v1Center.x() - v1Extent.x(), v1Center.y() - v1Extent.y(), v1Center.z() - v1Extent.z()));

    std::vector<PointCollision> collisions;
    for (auto& vertex : vertices)
    {
        std::vector<PointCollision> potentialCollisions;
        float insideOther = 6.0f;

        for (auto& face : faces)
        {
            float t = face.normal.dot(vertex - face.point);
            if (t < 0)
            {
                insideOther -= 1.0f;
                potentialCollisions.push_back({ vertex - face.normal * t, face.normal, -t });
            }
        }

        if (insideOther == 0.0f)
        {
            int min = 0;
            for (int i = 1; i < potentialCollisions.size(); i++)
            {
                if (potentialCollisions[i].penetration < potentialCollisions[min].penetration)
                {
                    min = i;
                }
            }
            collisions.push_back(potentialCollisions[min]);
        }
    }
    CollisionPair colPair;
    colPair.body1 = volume1->getRigidBody();
    colPair.body2 = volume2->getRigidBody();
    colPair.PointCollisions = collisions; // erreur de conversion
    colPair.atRest = false; // je sais pas comment déterminer ca, donc par défaut c'est false
    collisionPairs.push_back(colPair);
}
