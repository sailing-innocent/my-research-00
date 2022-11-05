$basePath = "E:/assets/shaders"
$folderName = "canvas"
# $folderName = "scene"

glslc "${basePath}/${folderName}/shader.vert" -o "${basePath}/${folderName}/vert.spv"
glslc "${basePath}/${folderName}/shader.frag" -o "${basePath}/${folderName}/frag.spv"