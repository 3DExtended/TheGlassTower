#pragma once

namespace engine
{
	class AModel
	{
	public:
		AModel();
		virtual ~AModel();

		virtual void render() = 0;
	};
}