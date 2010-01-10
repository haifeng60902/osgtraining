#ifndef _UFO_MANIPULATOR_H_
#define _UFO_MANIPULATOR_H_

#include <osgGA/MatrixManipulator>
#include <osg/Quat>

class UfoManipulator : public osgGA::MatrixManipulator
{
public:
	UfoManipulator();

	virtual const char* className() const { return "UfoManipulator"; }

	/** set the position of the matrix manipulator using a 4x4 Matrix.*/
	virtual void setByMatrix(const osg::Matrixd& matrix);

	/** set the position of the matrix manipulator using a 4x4 Matrix.*/
	virtual void setByInverseMatrix(const osg::Matrixd& matrix) { setByMatrix(osg::Matrixd::inverse(matrix)); }

	/** get the position of the manipulator as 4x4 Matrix.*/
	virtual osg::Matrixd getMatrix() const;

	/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
	virtual osg::Matrixd getInverseMatrix() const;


	virtual void setNode(osg::Node*);

	virtual const osg::Node* getNode() const;

	virtual osg::Node* getNode();

	virtual void home(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);

	virtual void init(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us);

        /** Get the keyboard and mouse usage of this manipulator.*/
        virtual void getUsage(osg::ApplicationUsage& usage) const;

    protected:

        virtual ~UfoManipulator();

        /** Reset the internal GUIEvent stack.*/
        void flushMouseEventStack();
        /** Add the current mouse GUIEvent to internal stack.*/
        void addMouseEvent(const osgGA::GUIEventAdapter& ea);

        void computePosition(const osg::Vec3& eye,const osg::Vec3& lv,const osg::Vec3& up);

        /** For the give mouse movement calculate the movement of the camera.
            Return true is camera has moved and a redraw is required.*/
        bool calcMovement();


        // Internal event stack comprising last three mouse events.
        osg::ref_ptr<const osgGA::GUIEventAdapter> m_GaT1;
        osg::ref_ptr<const osgGA::GUIEventAdapter> m_GaT0;

        osg::ref_ptr<osg::Node>       m_Node;

        float m_fModelScale;
        float m_fVelocity;

        osg::Vec3   m_v3Eye;
        osg::Quat   m_qRotation;
        float       m_fDistance;


};

#endif	//_UFO_MANIPULATOR_H_