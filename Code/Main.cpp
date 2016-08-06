#include "FengShuiEngine_PCH.h"
#include "FengShuiEngine.h"

int main(int argc, char** argv)
{
	FengShuiEngine* engine = FengShuiEngine::GetInstance();
		
	FengShuiEngine::Settings settings = engine->ParseStartArguments(argc, argv);

	if (!engine->Init(settings))
		return -1;

	engine->Run();

	return 0;
}