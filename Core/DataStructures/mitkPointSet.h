#ifndef MITKPointSet_H_HEADER_INCLUDED
#define MITKPointSet_H_HEADER_INCLUDED

#include <mitkCommon.h>
#include <mitkVector.h>
#include <mitkBaseData.h>
#include <itkPoint.h>
#include <itkPointSet.h>
#include <itkCovariantVector.h>
#include <itkMesh.h>
#include <itkDefaultDynamicMeshTraits.h>
#include <itkPolygonCell.h>
  
const unsigned int PointDimension = 3;
const unsigned int MaxTopologicalDimension = 3;


namespace mitk {

//##ModelId=3F0177E803A1
//##Documentation
//##@brief DataStructure which stores a set/list of Points 
//## @ingroup Data
//##
//## Each Entry (Point) in the the PointSet has a additional value (bool) to store
//## the selected/unselected state of the entry(Point).
//## Then each point has a type, like Startpoint or edge...
//## The class uses an itkMesh internaly. It can behave like a PointSet or due to the itkMesh like a PointList.
//## Inserting a point is accompanied by an event, containing an index. The new point is set into ths list 
//## at the indexed position. At the same time an internal ID is set in data of the point.
class PointSet : public BaseData
{
public:
  mitkClassMacro(PointSet, BaseData);

  itkNewMacro(Self);

  
  typedef mitk::ScalarType CoordinateType;
  typedef mitk::ScalarType InterpolationWeightType;
	//##Documentation
	//##@brief struct for data of a point
  typedef struct PointDataType 
  {
		unsigned int id;  //to give the point a special ID
    bool selected;  //information about if the point is selected
		mitk::PointSpecificationType pointSpec;  //specifies the type of the point
  };
  //##Documentation
	//##@brief cellDataType, that stores all indexes of the lines, that are selected
	//## e.g.: points A,B and C.Between A and B there is a line with index 0.
	//## if vector of cellData contains 1 and 2, then the lines between B and C and C and A is selected.
  typedef std::vector<int> SelectedLinesType;
  typedef std::vector<int>::iterator SelectedLinesIter;
  typedef struct CellDataType 
  {
    bool selected; //used to set the whole cell on selected
    SelectedLinesType selectedLines;//indexes of selected lines. 0 is between pointId 0 and 1
    bool closed; //is the polygon already finished and closed
  };

  typedef itk::DefaultDynamicMeshTraits<
    PointDataType, PointDimension, MaxTopologicalDimension, 
    CoordinateType, InterpolationWeightType, CellDataType > MeshTraits;
  typedef itk::Mesh<PointDataType, PointDimension, MeshTraits> MeshType;  

  typedef MeshType DataType;
  typedef DataType::PointType PointType;
  typedef DataType::PointsContainer PointsContainer;
  typedef DataType::PointsContainerIterator PointsIterator;
  typedef DataType::PointDataContainer PointDataContainer;
  typedef DataType::PointDataContainerIterator PointDataIterator;

  //##ModelId=3F0177E901BF
  //##Documentation
  //## @brief executes the given Operation
	virtual void ExecuteOperation(Operation* operation);

  //##ModelId=3F0177E901C1
  //##Documentation
	//## @brief returns the current size of the point-list
	virtual int GetSize();

  //##ModelId=3F0177E901CC
  //##Documentation
	//## @brief returns the pointset
  virtual DataType::Pointer GetPointSet() const;

  //##ModelId=3F0177E901CE
  //##Documentation
	//## @brief Get the point on the given position
  //##
  //## check if index exists. If it doesn't exist, then return 0,0,0
	const PointType GetPoint(int position);

  //##Documentation
  //## @brief searches a selected point and returns the id of that point. if no point is found, then -1 is returned
  virtual int SearchSelectedPoint();

  //##Documentation
	//## @brief returns true if a point exists at this position
  virtual bool IndexExists(int position);

  //##ModelId=3F0177E901DC
	//##Documentation
	//## @brief to get the state selected/unselected of the point on the position
	virtual bool GetSelectInfo(int position);

  //##ModelId=3F05B07B0147
  //##Documentation
	//## @brief returns the number of selected points
	virtual const int GetNumberOfSelected();

  //##ModelId=3F0177E901DE
	//##Documentation
	//## @brief searches a point in the List == point +/- distance
	//##
	//## returns -1 if no point is found
	//## or the position in the list of the first match
	int SearchPoint(Point3D point, float distance);

	//virtual methods, that need to be implemented
  //##ModelId=3F0177E901EE
	virtual void UpdateOutputInformation();
  //##ModelId=3F0177E901FB
	virtual void SetRequestedRegionToLargestPossibleRegion();
  //##ModelId=3F0177E901FD
	virtual bool RequestedRegionIsOutsideOfTheBufferedRegion();
  //##ModelId=3F0177E901FF
	virtual bool VerifyRequestedRegion();
  //##ModelId=3F0177E9020B
	virtual void SetRequestedRegion(itk::DataObject *data);

protected:
  //##ModelId=3F0177E901BD
	PointSet();

  //##ModelId=3F0177E901BE
	virtual ~PointSet();

  //##ModelId=3F0177E90190
	//##Documentation
	//## @brief Data from ITK; List of Points; the object, the operations are ment for
	DataType::Pointer m_ItkData;
};

} // namespace mitk



#endif /* MITKPointSet_H_HEADER_INCLUDED */
