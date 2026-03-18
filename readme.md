On top of the original Quake 1 SDK that I put together, this adds a shim layer for OpenGL that wraps everything to Direct3D 12. The shim layer handles the D3D12 layer,

any changes made to the codebase for it are marked(basically just in GL\_BeginRender/GL\_EndRender) everything else is Quake 1 exactly as Carmack released it.



This contains everything you need to create new custom games for Quake 1.
Compiles under Visual Studio 2022 with only changes needed for cmakefiles and to compile under C++(so typecasting).

