#include"Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
    cout << errno << std::endl;
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	
	string vertexCode = get_file_contents(vertexFile);
	string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create Fragment Shader Object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Create shader program 
	ID = glCreateProgram();

	// Attach both shaders to the program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Link the shader program
	glLinkProgram(ID);

	// Delete shaders after they have been attached
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::Activate() {
	// Use shader program
	glUseProgram(ID);
}