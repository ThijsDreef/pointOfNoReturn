#include "shaderManager.h"

std::string ShaderManager::readShader(const char * fileName)
{
  std::string shaderCode;
  std::ifstream file(fileName, std::ios::in);
  if (!file.good())
  {
    std::cout << "cant read shader: " << fileName << "\n";
    file.close();
    return shaderCode;
  }
  std::string line;
  while (std::getline(file, line))
    shaderCode += line + "\n";
  // file.seekg(0, std::ios::end);
  // shaderCode.resize((unsigned int)file.tellg());
  // file.seekg(0, std::ios::beg);
  // file.read(&shaderCode[0], shaderCode.size());
  // file.close();
  return shaderCode;
}

unsigned int ShaderManager::createShader(GLenum shaderType, std::string source, const char* shaderName)
{
  int compileResult = 0;
	unsigned int shader = glCreateShader(shaderType);
	const char * shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	//error check time
	if (compileResult == GL_FALSE)
	{
    std::cout << "shadercode size = " <<source.size() << "\n\n\n" << source << "\n";
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "error compiling shader: " << shaderName << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}
	return shader;
}

unsigned int ShaderManager::createShaderProgram(const char* vertex, const char* fragment, std::string shader)
{
  std::string vertexShaderCode = readShader(vertex);
	std::string fragmentShaderCode = readShader(fragment);
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex shader");
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment shader");
	int linkResult = 0;
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> program_log(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &program_log[0]);
		std::cout << "Shader Loader : Link Error " << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	shaderlist[shader] = program;
	return program;
}

unsigned int ShaderManager::getShader(std::string shader)
{
  return shaderlist[shader];
}

void ShaderManager::deleteShader(std::string shader)
{
  unsigned int p = shaderlist[shader];
  glDeleteProgram(p);
  shaderlist.erase(shader);
}

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{
  for (auto const &x : shaderlist)
    deleteShader(x.first);
}
