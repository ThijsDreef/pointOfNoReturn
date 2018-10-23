#include "System/Graphics/Geometry/geometry.h"

Geometry::Geometry()
{
  name = "error";
}

Geometry::Geometry(const char* fileName, const char* name, MaterialLib * materialLib)
{
  parseObj(fileName, materialLib);
    this->name = name;
}

void Geometry::setIndiceOffset(int offset)
{
  this->offset = offset;
  for (unsigned int i = 0; i < allIndices.size(); i++)
    for (unsigned int j = 0; j < allIndices[i].size(); j++)
      offsetIndices[i][j] = allIndices[i][j] + offset;
}

void loadFile(std::vector<unsigned char>& buffer, const std::string& filename) //designed for loading files from hard disk in an std::vector
{
  std::ifstream file(filename.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

  //get filesize
  std::streamsize size = 0;
  if(file.seekg(0, std::ios::end).good()) size = file.tellg();
  if(file.seekg(0, std::ios::beg).good()) size -= file.tellg();

  //read contents of the file into the vector
  if(size > 0)
  {
    buffer.resize((size_t)size);
    file.read((char*)(&buffer[0]), size);
  }
  else buffer.clear();
}

bool Geometry::parseObj(const std::string& name, MaterialLib * matlib)
{
  std::map<std::string, int> unique;
  int currentMaterialGroup = -1;
	Material currentMaterial;
	std::vector<int> verticesIndices;
	std::vector<int> normalsIndices;
	std::vector<int> textureIndices;
	std::vector<VertexFormat> finalVertices;
	std::vector<Vec3<float>> vertices;
	std::vector<Vec2<float>> texture;
	std::vector<Vec3<float>> normals;
	std::ifstream objFile(name);

	std::string line;
	if (objFile.is_open())
	{
		while (std::getline(objFile, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				Vec3<float> vertex;
				sscanf(line.c_str(), "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
				vertices.push_back(vertex);
			}
			else if (line.substr(0, 2) == "vn")
			{
				Vec3<float> vertex;
				sscanf(line.c_str(), "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
				normals.push_back(vertex);
			}
			else if (line.substr(0, 2) == "vt")
			{
				Vec2<float> vertex;
				sscanf(line.c_str(), "%*s %f %f", &vertex[0], &vertex[1]);
				//flip y coord for textures
				vertex[1] = 1 - vertex[1];
				texture.push_back(vertex);
			}
			else if (line.substr(0, 7) == "usemtl ")
			{
        materials.push_back(line.substr(7, line.size()));
        allIndices.push_back(std::vector<unsigned int>());
        offsetIndices.push_back(std::vector<unsigned int>());

				currentMaterialGroup ++;
			}
			else if (line.substr(0, 2) == "f ")
			{
        // make face using indices if indices match reuse the indice
				int vertexIndice[3];
				int uvIndice[3];
				int normalIndice[3];
        std::string indices[3];
				sscanf(line.c_str(), "%*s %i/%i/%i %i/%i/%i %i/%i/%i",
                                     &vertexIndice[0], &uvIndice[0], &normalIndice[0],
																	   &vertexIndice[1], &uvIndice[1], &normalIndice[1],
																	   &vertexIndice[2], &uvIndice[2], &normalIndice[2]);
        for (int i = 0; i < 3; i++)
        {
          indices[i] += std::to_string(vertexIndice[i]) + "/" + std::to_string(uvIndice[i]) + "/" + std::to_string(normalIndice[i]);
          auto it = unique.find(indices[i]);
          if (it == unique.end())
          {
            int indicePos = unique.size();
            unique[indices[i]] = indicePos;
            storedVertices.push_back(VertexFormat(vertices[vertexIndice[i] - 1], normals[normalIndice[i] - 1], texture[uvIndice[i] - 1]));
            allIndices[currentMaterialGroup].push_back(indicePos);
            offsetIndices[currentMaterialGroup].push_back(indicePos);
          }
          else
          {
            allIndices[currentMaterialGroup].push_back(unique[indices[i]]);
            offsetIndices[currentMaterialGroup].push_back(unique[indices[i]]);
          }
        }
			}
			else if (line.substr(0, 7) == "mtllib ")
			{
				std::ifstream mtlFile(name.substr(0, name.rfind("/") + 1) + line.substr(7, line.size()));
				std::string mtlLine;
				std::string currentMaterialName;
				while (std::getline(mtlFile, mtlLine))
				{
					if (mtlLine.substr(0, 7) == "map_Kd ")
					{
						//add texture here
						std::string textureName = name.substr(0, name.rfind("/") + 1) + mtlLine.substr(7, mtlLine.size());
						std::cout << "adding texture " << textureName;
		
						std::vector<unsigned char> buffer, image;
  					loadFile(buffer, textureName);
						unsigned long w, h;
  					int error = decodePNG(image, w, h, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size());	
						if (error) std::cout << error << " " <<" error code with loading texture\n";
						Texture * texture = new Texture(w, h, GL_RGBA, GL_RGBA, GL_LINEAR, GL_UNSIGNED_BYTE, &image[0], textureName);
						matlib->addTexture(textureName, texture);
						currentMaterial.texture = texture->getId();
						std::cout << " id" << currentMaterial.texture << "\n";
						
					}
          // wil work as long as material only supports color
					if (mtlLine.substr(0, 3) == "Kd ")
					{
						Vec4<float> matColor;
						matColor[3] = 1;
						sscanf(mtlLine.c_str(), "%*s %f %f %f", &matColor[0], &matColor[1], &matColor[2]);
						currentMaterial.color = matColor;
					}
					else if (mtlLine.substr(0, 7) == "newmtl ")
					{
						matlib->addMaterial(currentMaterialName, currentMaterial);
						currentMaterialName = mtlLine.substr(7, mtlLine.size());
						currentMaterial = Material();
					}
				}
				mtlFile.close();
			}
		}
	}
  objFile.close();
  return true;
}

const std::vector<unsigned int>& Geometry::getIndice(int group)
{
  return offsetIndices[group];
}


const std::vector<std::string>&Geometry::getMaterials()
{
  return materials;
}

Geometry::~Geometry()
{

}
