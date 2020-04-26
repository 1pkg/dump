#ifndef __RESOURCES_UNITED_RESOURCES_DATA_HPP__
#define __RESOURCES_UNITED_RESOURCES_DATA_HPP__

namespace Resources
{

class UnitedResourcesData
{
public:

	UnitedResourcesData();
	UnitedResourcesData( unsigned int size );
	UnitedResourcesData( unsigned char * data, unsigned int size );
	~UnitedResourcesData();

	UnitedResourcesData( const UnitedResourcesData & data );
	UnitedResourcesData & operator=( const UnitedResourcesData & data );

	UnitedResourcesData( UnitedResourcesData && data );
	UnitedResourcesData & operator=( UnitedResourcesData && data );

	unsigned int size() const;
	unsigned char * data() const;

	bool empty() const;

	void append( const UnitedResourcesData & data );
	void append( unsigned char * data, unsigned int size );

	void move( unsigned int size );

	void toFit();

private:

	unsigned int _used;
	unsigned int _size;
	unsigned char * _data;

	unsigned char * _top;
};

}

#endif