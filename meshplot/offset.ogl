/*
 * offset.vrx
 *
 *  Created on: May 13th, 2021
 *      Author: Dr. R. Poller
 *
 *  Task
 *      Vertex shader for offsetting the displayed mesh
 *
 */

#version 140
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 position;
 
void main()
{
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * position;
}
 