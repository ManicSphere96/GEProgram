//#pragma once
#ifdef BU_GL_H
  #error This header file should never need to be included twice!
#endif
#define BU_GL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>


namespace bu
{

struct Face
{
  glm::vec3 pa;
  glm::vec3 pb;
  glm::vec3 pc;

  glm::vec2 tca;
  glm::vec2 tcb;
  glm::vec2 tcc;

  glm::vec3 na;
  glm::vec3 nb;
  glm::vec3 nc;

  glm::vec2 lmca;
  glm::vec2 lmcb;
  glm::vec2 lmcc;
};

struct ConvexPlane
{
    glm::vec3 point;
    glm::vec3 normal;
};

template <typename T>
void splitStringWhitespace(const std::string& input,
  std::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == ' ' ||
      input.at(i) == '\r' ||
      input.at(i) == '\n' ||
      input.at(i) == '\t')
    {
      if(curr.length() > 0)
      {
        output.push_back(curr);
        curr = "";
      }
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

template <typename T>
void splitString(const std::string& input, char splitter,
  std::vector<std::string>& output)
{
  std::string curr;

  output.clear();

  for(size_t i = 0; i < input.length(); i++)
  {
    if(input.at(i) == splitter)
    {
      output.push_back(curr);
      curr = "";
    }
    else
    {
      curr += input.at(i);
    }
  }

  if(curr.length() > 0)
  {
    output.push_back(curr);
  }
}

template <typename T>
size_t loadModel(const std::string& path,
  GLuint *positionsId, GLuint *tcsId, GLuint *normalsId, std::vector<ConvexPlane>& convexPlanes,
  std::string& currentLine)
{
  std::vector<glm::vec3> positions;
  std::vector<glm::vec2> tcs;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> lmcs;
  std::vector<Face> faces;

  *positionsId = 0;
  *tcsId = 0;
  *normalsId = 0;

  std::ifstream file(path.c_str());
  

  if(!file.is_open())
  {
    throw std::exception();
  }

  while(!file.eof())
  {
    std::getline(file, currentLine);
    if(currentLine.length() < 1) continue;
    //std::cout << "Line [" << currentLine << "]" << std::endl;

    std::vector<std::string> tokens;
    splitStringWhitespace<int>(currentLine, tokens);
    if(tokens.size() < 1) continue;

    if(tokens.at(0) == "v")
    {
      glm::vec3 p(atof(tokens.at(1).c_str()),
        atof(tokens.at(2).c_str()),
        atof(tokens.at(3).c_str()));

      positions.push_back(p);
    }
    else if(tokens.at(0) == "vt")
    {
      glm::vec2 tc(atof(tokens.at(1).c_str()),
        1.0f - atof(tokens.at(2).c_str()));

      tcs.push_back(tc);
    }
    else if(tokens.at(0) == "vn")
    {
      glm::vec3 n(atof(tokens.at(1).c_str()),
        atof(tokens.at(2).c_str()),
        atof(tokens.at(3).c_str()));

      normals.push_back(n);
    }
    else if(tokens.at(0) == "f")
    {
      if(tokens.size() < 4) continue;

      Face f;
      std::vector<std::string> sub;
      splitString<int>(tokens.at(1), '/', sub);
      if(sub.size() >= 1) f.pa = positions.at(atoi(sub.at(0).c_str()) - 1);
      if(sub.size() >= 2) f.tca = tcs.at(atoi(sub.at(1).c_str()) - 1);
      if(sub.size() >= 3) f.na = normals.at(atoi(sub.at(2).c_str()) - 1);
      if(sub.size() >= 4) f.lmca = lmcs.at(atoi(sub.at(3).c_str()) - 1);

      splitString<int>(tokens.at(2), '/', sub);
      if(sub.size() >= 1) f.pb = positions.at(atoi(sub.at(0).c_str()) - 1);
      if(sub.size() >= 2) f.tcb = tcs.at(atoi(sub.at(1).c_str()) - 1);
      if(sub.size() >= 3) f.nb = normals.at(atoi(sub.at(2).c_str()) - 1);
      if(sub.size() >= 4) f.lmcb = lmcs.at(atoi(sub.at(3).c_str()) - 1);

      splitString<int>(tokens.at(3), '/', sub);
      if(sub.size() >= 1) f.pc = positions.at(atoi(sub.at(0).c_str()) - 1);
      if(sub.size() >= 2) f.tcc = tcs.at(atoi(sub.at(1).c_str()) - 1);
      if(sub.size() >= 3) f.nc = normals.at(atoi(sub.at(2).c_str()) - 1);
      if(sub.size() >= 4) f.lmcc = lmcs.at(atoi(sub.at(3).c_str()) - 1);

      faces.push_back(f);
      if(tokens.size() < 5) continue;

      Face fq;
      fq.pa = f.pc;
      fq.tca = f.tcc;
      fq.na = f.nc;
      fq.lmca = f.lmcc;

      splitString<int>(tokens.at(4), '/', sub);
      if(sub.size() >= 1) fq.pb = positions.at(atoi(sub.at(0).c_str()) - 1);
      if(sub.size() >= 2) fq.tcb = tcs.at(atoi(sub.at(1).c_str()) - 1);
      if(sub.size() >= 3) fq.nb = normals.at(atoi(sub.at(2).c_str()) - 1);
      if(sub.size() >= 4) fq.lmcb = lmcs.at(atoi(sub.at(3).c_str()) - 1);

      fq.pc = f.pa;
      fq.tcc = f.tca;
      fq.nc = f.na;
      fq.lmcc = f.lmca;

      faces.push_back(fq);
    }
  }

  GLuint vboId = 0;

  if(positions.size() < 1)
  {
    currentLine = "No positions specified";
    throw std::exception();
  }

  size_t rtn = faces.size() * 3;

  {
    std::vector<float> b;

    for(std::vector<Face>::iterator fit = faces.begin();
      fit != faces.end(); fit++)
    {
      b.push_back(fit->pa.x); b.push_back(fit->pa.y); b.push_back(fit->pa.z);
      b.push_back(fit->pb.x); b.push_back(fit->pb.y); b.push_back(fit->pb.z);
      b.push_back(fit->pc.x); b.push_back(fit->pc.y); b.push_back(fit->pc.z);
    }

    glGenBuffers(1, &vboId);

    if(!vboId)
    {
      throw std::exception();
    }

    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(b.at(0)) * b.size(), &b.at(0),
      GL_STATIC_DRAW);

    *positionsId = vboId;
  }

  if(tcs.size() > 0)
  {
    std::vector<float> b;

    for(std::vector<Face>::iterator fit = faces.begin();
      fit != faces.end(); fit++)
    {
      b.push_back(fit->tca.x); b.push_back(fit->tca.y);
      b.push_back(fit->tcb.x); b.push_back(fit->tcb.y);
      b.push_back(fit->tcc.x); b.push_back(fit->tcc.y);
    }

    glGenBuffers(1, &vboId);

    if(!vboId)
    {
      throw std::exception();
    }

    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(b.at(0)) * b.size(), &b.at(0),
      GL_STATIC_DRAW);

    *tcsId = vboId;
  }

  if(normals.size() > 0)
  {
    std::vector<float> b;

    for(std::vector<Face>::iterator fit = faces.begin();
      fit != faces.end(); fit++)
    {
      b.push_back(fit->na.x); b.push_back(fit->na.y); b.push_back(fit->na.z);
      b.push_back(fit->nb.x); b.push_back(fit->nb.y); b.push_back(fit->nb.z);
      b.push_back(fit->nc.x); b.push_back(fit->nc.y); b.push_back(fit->nc.z);
    }

    glGenBuffers(1, &vboId);

    if(!vboId)
    {
      throw std::exception();
    }

    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(b.at(0)) * b.size(), &b.at(0),
      GL_STATIC_DRAW);

    *normalsId = vboId;
  }

  if(lmcs.size() > 0)
  {
    // TODO
  }

  // std::vector<ConvexPlane> convexPlanes
  for (int fi = 0; fi < (int)faces.size(); fi++)
  {
      ConvexPlane cp;
      cp.point = faces[fi].pa;
      cp.normal = faces[fi].na;
      bool dupFound = false;
      for (int cpj = 0; cpj < (int)convexPlanes.size(); cpj++)
       {
          if (convexPlanes[cpj].normal == cp.normal)
          { 
              dupFound = true;
              break;
          }
      }
      if (!dupFound) convexPlanes.push_back(cp);
  }


  return rtn;
}

template <typename T>
size_t loadModel(const std::string& path,
  GLuint *positionsId, GLuint *tcsId, GLuint *normalsId, std::vector<ConvexPlane> *convexPlanes)
{
  std::string currentLine = path;

  try
  {
    return loadModel<int>(path, positionsId, tcsId, normalsId, *convexPlanes, currentLine);
  }
  catch(std::exception& e)
  {
    std::cout << "Failed to parse model data [" + currentLine + "]"
      << std::endl;

    throw std::runtime_error("Failed to parse model data [" + currentLine + "]");
  }
}

}

#define buLoadModel bu::loadModel<int>
