#include "util.h"

namespace UtilLoader
{
  void loadResources(GeometryLib& geoLib, MaterialLib& matlib)
  {
    //load resources.txt

    std::ifstream resourceFile("resource.txt");
    std::string rsLine;
    while (std::getline(resourceFile, rsLine))
    {
      //read lines that end with .obj
      //then load these files into the geolib
      if (rsLine.substr(rsLine.size() - 4, rsLine.size()) == ".obj")
      {
        std::string name = rsLine.substr(rsLine.rfind("/") + 1);
        name = name.substr(0, name.size() - 4);
        std::cout << "parsing " << name << "\n";

        geoLib.addGeometry(Geometry(rsLine.c_str(), name.c_str(), &matlib));
      }
    }
  }

} /* UtilLoader */
