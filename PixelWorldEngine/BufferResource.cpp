#include "BufferResource.hpp"

#include "Application.hpp"
#include "Graphics.hpp"

PixelWorldEngine::Graphics::Buffer::Buffer(void * data, int dataSize, int dataCount, BufferType bufferType)
{
	graphics = Application::GetGraphicsInstance();

	size = dataSize;
	count = dataCount;
	type = bufferType;

#ifdef WINDOWS

	
	desc.BindFlags = (D3D11_BIND_FLAG)type;
	desc.ByteWidth = size;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = size / count;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	graphics->device->CreateBuffer(&desc, nullptr, &buffer);

#endif // WINDOWS

	Update(data);
}

PixelWorldEngine::Graphics::Buffer::~Buffer() 
{
#ifdef WINDOWS
	Utility::Dipose(buffer);
#endif // WINDOWS

}

void PixelWorldEngine::Graphics::Buffer::Update(void * data)
{
	graphics->deviceContext->UpdateSubresource(buffer, 0, nullptr,
		data, 0, 0);
}

auto PixelWorldEngine::Graphics::Buffer::GetSize() -> int
{
	return size;
}

auto PixelWorldEngine::Graphics::Buffer::GetCount() -> int
{
	return count;
}

auto PixelWorldEngine::Graphics::Buffer::GetType() -> BufferType
{
	return type;
}

auto PixelWorldEngine::Graphics::Buffer::GetResource() -> void *
{
#ifdef WINDOWS
	return buffer;
#endif
}


