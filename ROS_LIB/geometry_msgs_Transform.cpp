#include "geometry_msgs_Transform.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
geometry_msgs_Transform::geometry_msgs_Transform()
{
	this->m_rotation.setX(0);
	this->m_rotation.setY(0);
	this->m_rotation.setZ(0);
	this->m_rotation.setW(1);
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
geometry_msgs_Transform::~geometry_msgs_Transform()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject geometry_msgs_Transform::getJsonObj()
{

	QJsonObject Transform;	
	
	QJsonObject translation;	
	QJsonObject rotation;
	
	translation.insert("x", m_translation.x());
	translation.insert("y", m_translation.y());
	translation.insert("z", m_translation.z());

	rotation.insert("x", m_rotation.x());
	rotation.insert("y", m_rotation.y());
	rotation.insert("z", m_rotation.z());
	rotation.insert("w", m_rotation.w());

	Transform.insert("translation",translation);
	Transform.insert("rotation",rotation);

	return Transform;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/