#include "DynamicHouseUpdateCallback.h"

#include "../VisiblePatchArray.h"

DynamicHouseUpdateCallback::DynamicHouseUpdateCallback()
{

}

void DynamicHouseUpdateCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	//вернуть ссылку на массив видимых патчей
	const std::vector< dataPatch > &data_vis = VisiblePatchArray::Instance().GetVisibleArray512();

	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);
}