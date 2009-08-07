#include "BranchXMLWindCallback.h"

#include <osg/MatrixTransform>
#include <osg/Timer>

BranchXMLWindCallback::BranchXMLWindCallback() : m_fWindStrength( 1.0f )
{
	//всего 4 матрицы ветра
	m_vWM.resize( 4 );

	//матрицы 4х4
	m_vWM[0].resize( 16 );
	m_vWM[1].resize( 16 );
	m_vWM[2].resize( 16 );
	m_vWM[3].resize( 16 );
}

BranchXMLWindCallback::~BranchXMLWindCallback()
{

}

void BranchXMLWindCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	double time = osg::Timer::instance()->time_s();

	//вычислить матрицы ветра
	SetupWindMatrices( time );

	osg::Matrix m0( &m_vWM[0][0] );
	osg::Matrix m1( &m_vWM[1][0] );
	osg::Matrix m2( &m_vWM[2][0] );
	osg::Matrix m3( &m_vWM[3][0] );

	m_vUM[0]->set( m0 );
	m_vUM[1]->set( m1 );
	m_vUM[2]->set( m2 );
	m_vUM[3]->set( m3 );
	
	// Continue traversing so that OSG can process
	//   any other nodes with callbacks.
	traverse( node, nv );
}

void BranchXMLWindCallback::SetupWindMatrices( float fTimeInSecs )
{
	// matrix computational data
	static int c_nNumWindMatrices = 4;
	static float afMatrixTimes[4] = { 0.0f };
	static float afFrequencies[4][2] = 
	{
		{ 0.15f, 0.17f },
		{ 0.25f, 0.15f },
		{ 0.19f, 0.05f },
		{ 0.15f, 0.22f }
	};

	// compute time since last call
	static float fTimeOfLastCall = 0.0f;
	float fTimeSinceLastCall = fTimeInSecs - fTimeOfLastCall;
	fTimeOfLastCall = fTimeInSecs;

	// wind strength
	static float fOldStrength = m_fWindStrength;

	// increment matrix times
	for (int i = 0; i < c_nNumWindMatrices; ++i)
		afMatrixTimes[i] += fTimeSinceLastCall;

	// compute maximum branch throw
	float fBaseAngle = m_fWindStrength * 35.0f;

	// build rotation matrices
	for (int i = 0; i < c_nNumWindMatrices; ++i)
	{
		// adjust time to prevent "jumping"
		if (m_fWindStrength != 0.0f)
			afMatrixTimes[i] = (afMatrixTimes[i] * fOldStrength) / m_fWindStrength;

		// compute percentages for each axis
		float fBaseFreq = m_fWindStrength * 20.0f;
		float fXPercent = sinf(fBaseFreq * afFrequencies[i % c_nNumWindMatrices][0] * afMatrixTimes[i]);
		float fYPercent = cosf(fBaseFreq * afFrequencies[i % c_nNumWindMatrices][1] * afMatrixTimes[i]);

		// build compound rotation matrix (rotate on 'x' then on 'y')
		const float c_fDeg2Rad = 57.2957795f;
		float fSinX = sinf(fBaseAngle * fXPercent / c_fDeg2Rad);
		float fSinY = sinf(fBaseAngle * fYPercent / c_fDeg2Rad);
		float fCosX = cosf(fBaseAngle * fXPercent / c_fDeg2Rad);
		float fCosY = cosf(fBaseAngle * fYPercent / c_fDeg2Rad);

		float afMatrix[16] = { 0.0f };
		afMatrix[0] = fCosY;
		afMatrix[2] = -fSinY;
		afMatrix[4] = fSinX * fSinY;
		afMatrix[5] = fCosX;
		afMatrix[6] = fSinX * fCosY;
		afMatrix[8] = fSinY * fCosX;
		afMatrix[9] = -fSinX;
		afMatrix[10] = fCosX * fCosY;
		afMatrix[15] = 1.0f;

		//////////////////////////////////////////////////////////////////////////
		//копируем матрицы
		for ( int j = 0 ; j < 16 ; ++j )
			m_vWM[ i ][ j ] = afMatrix[ j ];
	}

	// track wind strength
	fOldStrength = m_fWindStrength;
}