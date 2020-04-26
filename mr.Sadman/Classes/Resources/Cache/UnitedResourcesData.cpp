#include "UnitedResourcesData.hpp"

#include <memory>
#include <stdio.h>
#include <string.h>

namespace Resources
{

UnitedResourcesData::UnitedResourcesData()
	: _data( nullptr ), _top( nullptr ), _size( 0 ), _used( 0 )
{
}

UnitedResourcesData::UnitedResourcesData( unsigned int size )
	: _data( new unsigned char[ size ] ), _size( size ), _used( 0 )
{
	_top = _data;
}

UnitedResourcesData::UnitedResourcesData( unsigned char * data, unsigned int size )
	: _data( new unsigned char[ size ] ), _size( size ), _used( size )
{
	memcpy( _data, data, _size );
	_top = _data;
}

UnitedResourcesData::~UnitedResourcesData()
{
	delete[] _top;
}

UnitedResourcesData::UnitedResourcesData( const UnitedResourcesData & data )
{
	_size = data._size;
	_used = data._used;
	_data = new unsigned char[ _size ];
	memcpy( _data, data._data, _size );
	_top = _data;
}

UnitedResourcesData &
UnitedResourcesData::operator=( const UnitedResourcesData & data )
{
	delete[] _top;
	_size = data._size;
	_used = data._used;
	_data = new unsigned char[ _size ];
	memcpy( _data, data._data, _size );
	_top = _data;

	return *this;
}

UnitedResourcesData::UnitedResourcesData( UnitedResourcesData && data )
{
	_size = data._size;
	_used = data._used;
	_data = data._data;
	_top = data._top;

	data._data = nullptr;
	data._top = nullptr;
}

UnitedResourcesData &
UnitedResourcesData::operator=( UnitedResourcesData && data )
{
	_size = data._size;
	_used = data._used;
	std::swap( _data, data._data );
	std::swap( _top, data._top );

	return *this;
}

unsigned int
UnitedResourcesData::size() const
{
	return _size;
}

unsigned char *
UnitedResourcesData::data() const
{
	return _data;
}

bool
UnitedResourcesData::empty() const
{
	return _used == 0;
}

void
UnitedResourcesData::append( const UnitedResourcesData & data )
{
	memcpy( _data + _used, data._data, data._size );
	_used += data._size;
}

void
UnitedResourcesData::append( unsigned char * data, unsigned int size )
{
	append( UnitedResourcesData( data, size ) );
}

void
UnitedResourcesData::move( unsigned int size )
{
	_data += size;
	_size -= size;
}

void
UnitedResourcesData::toFit()
{
	_size = _used;
}


}