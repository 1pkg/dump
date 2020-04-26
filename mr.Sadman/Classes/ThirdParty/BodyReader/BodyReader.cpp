#include "BodyReader.hpp"

namespace ThirdParty
{

BodyReader & BodyReader::getInstance()
{
	static BodyReader reader;
	return reader;
}

BodyReader::BodyReader()
{
}

void BodyReader::parse( unsigned char *buffer, long length )
{
    bool result = false;
    std::string js((const char*)buffer, length);
    _doc.Parse<0>(js.c_str());
}

void BodyReader::parseJsonFile( const std::string& pFile )
{
    auto content = FileUtils::getInstance()->getDataFromFile( pFile );
    parse( content.getBytes(), content.getSize() );
}

PhysicsBody * BodyReader::getBody( unsigned char* stream, long length, Node* pNode, const std::string& name, PhysicsMaterial material )
{
	parse(stream, length);
    PhysicsBody* body = nullptr;

    rapidjson::Value &bodies = _doc["rigidBodies"];
    if (bodies.IsArray())
    {
        for (unsigned int i=0; i<bodies.Size(); ++i)
        {
            if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
            {
                rapidjson::Value &bd = bodies[i];
                if (bd.IsObject())
                {
                    body = PhysicsBody::create();
                    float width = pNode->getContentSize().width;
                    float offx = - pNode->getAnchorPoint().x*pNode->getContentSize().width;
                    float offy = - pNode->getAnchorPoint().y*pNode->getContentSize().height;

                    Point origin( bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
                    rapidjson::Value &polygons = bd["polygons"];
                    for (unsigned int i = 0; i<polygons.Size(); ++i)
                    {
                        int pcount = polygons[i].Size();
                        Point* points = new Point[pcount];
                        for (int pi = 0; pi<pcount; ++pi)
                        {
                            points[pi].x = offx + width * polygons[i][pcount-1-pi]["x"].GetDouble();
                            points[pi].y = offy + width * polygons[i][pcount-1-pi]["y"].GetDouble();
                        }
                        body->addShape(PhysicsShapePolygon::create(points, pcount, material));
                        delete [] points;
                    }
                }
                else
                {
                    CCLOG("body: %s not found!", name.c_str());
                }
                break;
            }
        }
    }
    return body;
}

}