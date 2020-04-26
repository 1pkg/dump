#include "GameAct/Act.hpp"
#include "../Contours/Kit.hpp"
#include "../Contours/Segment.hpp"
#include "../Contours/KitExpert.hpp"
#include "Interactor.hpp"
#include "Registry.hpp"
#include "Character.hpp"
#include "Requires/Spikes.hpp"
#include "Requires/Edge.hpp"
#include "Resources/Constants.hpp"

namespace GameAct
{

namespace Objects
{

void
Registry::update(cocos2d::Vec2 delta) 
{
	return;
}

void
Registry::render() const
{
	return;
}

cocos2d::Rect
Registry::getBoundingBox() const
{
	return cocos2d::Rect();
}

bool
Registry::handle(const Interfaces::IObserverable * obsable)
{
	const Interfaces::IObjectView * object = dynamic_cast<const Interfaces::IObjectView *>(obsable);
	if(!object)
		return false;

	auto it = std::find_if(
		_objects.begin(),
		_objects.end(),
		[object](const std::unique_ptr<Interfaces::IObjectView> & obj)
		{
			return obj.get() == object;
		}
	);
	_objects.erase(it);

	return true;
}

Registry::Registry(Interactor * interactor, cocos2d::Layer * layer)
	: _interactor(interactor), generator(this), _layer(layer), _physicListener(cocos2d::EventListenerPhysicsContact::create())
{
	/*			PhysicsSetup			*/
				/**/

	/*			RequiresSetup			*/
	_objects.insert(std::move(std::unique_ptr<Interfaces::IObjectView>(new Requires::Edge(_layer))));
	_objects.insert(std::move(std::unique_ptr<Interfaces::IObjectView>(new Requires::Spikes(_layer))));

				/**/

	/*			UpdateAction			*/
	auto updateObjects = [this](float)
	{
		for(auto it = _objects.begin(); it != _objects.end();)
		{
			if((*it)->getBoundingBox().origin.x < Resources::Constants::SCENE_OBJECT_DYING_POSITION_SCALE * cocos2d::Director::getInstance()->getVisibleSize().width)
				it = _objects.erase(it);
			else
				++it;
		}	
	};
	_layer->schedule(updateObjects, Resources::Constants::OBJECT_REALESE_TIME, "RegistryUpdate");
				/**/

	/*			GeneratorAction			*/
	_layer->schedule(std::bind(&Generator::update, &generator), Resources::Constants::GENERATOR_UPDATE_TIME, "GeneratorUpdate");
				/**/

	/*			PhysicController			*/
	_physicListener->onContactBegin = [this](cocos2d::PhysicsContact & contact)
	{
		cocos2d::PhysicsBody* bodyA = contact.getShapeA()->getBody();
		cocos2d::PhysicsBody* bodyB = contact.getShapeB()->getBody();
		return this->contact(bodyA, bodyB);
	};
	_physicListener->onContactSeparate = [this](cocos2d::PhysicsContact & separate)
	{
		cocos2d::PhysicsBody* bodyA = separate.getShapeA()->getBody();
		cocos2d::PhysicsBody* bodyB = separate.getShapeB()->getBody();
		this->separate(bodyA, bodyB);
	}; 
	_layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_physicListener, _layer);
				/**/
}

Registry::~Registry()
{
	_layer->getEventDispatcher()->removeEventListener(_physicListener);

	_layer->unschedule("GeneratorUpdate");

	_layer->unschedule("RegistryUpdate");
}

Interfaces::IObjectView *
Registry::findObjectView(cocos2d::PhysicsBody * body) const
{
	for(auto & obj : _objects)
		if(obj->getPhysicsBody() == body)
			return obj.get();

	return nullptr;
}

bool
Registry::intersect(cocos2d::Rect rect) const
{
	for(auto & obj : _objects)
		if(obj->getBoundingBox().intersectsRect(rect))
			return true;

	return false;
}

bool
Registry::contact(cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr)
{
	Contact contact = find(objl, objr);

	if((contact.pair.first == contact.pair.second) || (!contact.pair.first || !contact.pair.second) || std::find(_contacts.begin(), _contacts.end(), contact) != _contacts.end())
		return true;

	return _interactor->interact(contact.pair.first, contact.pair.second)
	? _contacts.push_back(contact), true
	: false;
}

void
Registry::separate(cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr)
{
	Contact contact = find(objl, objr);

	if((contact.pair.first == contact.pair.second) || (!contact.pair.first || !contact.pair.second) || std::find(_contacts.begin(), _contacts.end(), contact ) == _contacts.end())
		return;

	_contacts.erase(std::remove(_contacts.begin(), _contacts.end(), contact));
}

Registry::Contact
Registry::find(cocos2d::PhysicsBody * objl, cocos2d::PhysicsBody * objr)
{
	Contact result = Contact({nullptr, nullptr});

	Interfaces::IObject * obj1 = findObjectView(objl);

	if(!obj1)
		obj1 = GameAct::Act::getInstance().getKit()->findObjectView(objl);

	if(!obj1 && GameAct::Act::getInstance().getCharacter()->getPhysicsBody() == objl)
		obj1 = GameAct::Act::getInstance().getCharacter();

	Interfaces::IObject * obj2 = findObjectView(objr);

	if(!obj2)
		obj2 = GameAct::Act::getInstance().getKit()->findObjectView(objr);

	if(!obj2 && GameAct::Act::getInstance().getCharacter()->getPhysicsBody() == objr)
		obj2 = GameAct::Act::getInstance().getCharacter();

	result.pair.first = obj1;
	result.pair.second = obj2;

	return result;
}

}

}