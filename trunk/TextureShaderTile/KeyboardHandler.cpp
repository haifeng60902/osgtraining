#include "KeyboardHandler.h"

#include <osgViewer/Viewer>

#include <iostream>

KeyboardHandler::KeyboardHandler() : m_fOffsetX( 0.0f ) 
, m_fOffsetY( 0.0f )
, m_fScaleX( 0.0f )
, m_fScaleY( 0.0f )
, m_fOffsetScaleX( 0.0f )
, m_fOffsetScaleY( 0.0f )
{

}

KeyboardHandler::~KeyboardHandler()
{

}

bool KeyboardHandler::handle( const osgGA::GUIEventAdapter& ea,
			osgGA::GUIActionAdapter& aa )
{
	osgViewer::Viewer* viewer =
		dynamic_cast<osgViewer::Viewer*>( &aa );
	if (!viewer)
		return( false );

	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			if ( ea.getKey()=='o' )
			{
				m_fOffsetX += 1.0;
				m_OffsetX->set( m_fOffsetX / 32768.0f );
				std::cout << "m_fOffsetX: " << m_fOffsetX << "\n";
			}
			else
				if ( ea.getKey()=='O' )
				{
					m_fOffsetX -= 1.0;
					m_OffsetX->set( m_fOffsetX / 32768.0f );
					std::cout << "m_fOffsetX: " << m_fOffsetX << "\n";
				}
				else
					if ( ea.getKey()=='p' )
					{
						m_fOffsetY += 1.0;
						m_OffsetY->set( m_fOffsetY / 8196.0f );
						std::cout << "m_fOffsetY: " << m_fOffsetY << "\n";
					}
					else
						if ( ea.getKey()=='P' )
						{
							m_fOffsetY -= 1.0;
							m_OffsetY->set( m_fOffsetY / 8196.0f );
							std::cout << "m_fOffsetY: " << m_fOffsetY << "\n";
						}
						else
							if ( ea.getKey()=='x' )
							{
								m_fScaleX += 1.0;
								m_ScaleX->set( 1.0f + m_fScaleX / 8196.0f );
								std::cout << "m_fScaleX: " << m_fScaleX << "\n";
							}
							else
								if ( ea.getKey()=='X' )
								{
									m_fScaleX -= 1.0;
									m_ScaleX->set( 1.0f + m_fScaleX / 8196.0f );
									std::cout << "m_fScaleX: " << m_fScaleX << "\n";
								}
								else
									if ( ea.getKey()=='c' )
									{
										m_fScaleY += 1.0;
										m_ScaleY->set( 1.0f + m_fScaleY / 8196.0f );
										std::cout << "m_fScaleY: " << m_fScaleY << "\n";
									}
									else
										if ( ea.getKey()=='C' )
										{
											m_fScaleY -= 1.0;
											m_ScaleY->set( 1.0f + m_fScaleY / 8196.0f );
											std::cout << "m_fScaleY: " << m_fScaleY << "\n";
										}
										else
											if ( ea.getKey()=='v' )
											{
												m_fOffsetScaleX += 1.0;
												m_OffsetScaleX->set( m_fOffsetScaleX / 1024.0f );
												std::cout << "m_fOffsetScaleX: " << m_fOffsetScaleX << "\n";
											}
											else
												if ( ea.getKey()=='V' )
												{
													m_fOffsetScaleX -= 1.0;
													m_OffsetScaleX->set( m_fOffsetScaleX / 1024.0f );
													std::cout << "m_fOffsetScaleX: " << m_fOffsetScaleX << "\n";
												}
												else
													if ( ea.getKey()=='b' )
													{
														m_fOffsetScaleY += 1.0;
														m_OffsetScaleY->set( m_fOffsetScaleY / 1024.0f );
														std::cout << "m_fOffsetScaleY: " << m_fOffsetScaleY << "\n";
													}
													else
														if ( ea.getKey()=='B' )
														{
															m_fOffsetScaleY -= 1.0;
															m_OffsetScaleY->set( m_fOffsetScaleY / 1024.0f );
															std::cout << "m_fOffsetScaleY: " << m_fOffsetScaleY << "\n";
														}

			return false;
		}

	default:
		return false;
	}

	return false;
}