#include "GL_Wrapper/ElementBuffer.hpp"

using namespace GL_Wrapper;

ElementBuffer::ElementBuffer(const unsigned int *data, size_t count)
{
	GLCallThrow(glGenBuffers(1, &this->_id));
	try {
		GLCallThrow(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id));
		GLCallThrow(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	} catch (...) {
		glDeleteBuffers(1, &this->_id);
		throw;
	}
}

ElementBuffer::~ElementBuffer(void)
{
	glDeleteBuffers(1, &this->_id);
}

void	ElementBuffer::bind(void) const
{
	GLCallThrow(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id));
}

void	ElementBuffer::unbind(void) const
{
	GLCallThrow(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}