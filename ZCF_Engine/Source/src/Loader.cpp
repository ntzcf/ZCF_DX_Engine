#include "Scene/Loader.h"
#include <intsafe.h>
#include "Scene/SceneManager.h"

namespace Engine::scene::Loader
{
	Model::Model(const std::string& path , uint32_t UV_nums , uint32_t MatID) :UV_nums(UV_nums), MatID(MatID)
	{
		Assimp::Importer localImporter;

		const aiScene* pLocalScene = localImporter.ReadFile(
			path,
			// Triangulates all faces of all meshes
			aiProcess_Triangulate |
			// Supersedes the aiProcess_MakeLeftHanded and aiProcess_FlipUVs and aiProcess_FlipWindingOrder flags
			aiProcess_ConvertToLeftHanded |
			// This preset enables almost every optimization step to achieve perfectly optimized data. In D3D, need combine with aiProcess_ConvertToLeftHanded
			aiProcessPreset_TargetRealtime_MaxQuality |
			// Calculates the tangents and bitangents for the imported meshes
			aiProcess_CalcTangentSpace |
			// Splits large meshes into smaller sub-meshes
			// This is quite useful for real-time rendering, 
			// where the number of triangles which can be maximally processed in a single draw - call is limited by the video driver / hardware
			aiProcess_SplitLargeMeshes |
			// A postprocessing step to reduce the number of meshes
			aiProcess_OptimizeMeshes |
			// A postprocessing step to optimize the scene hierarchy
			aiProcess_OptimizeGraph);

		// "localScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE" is used to check whether value data returned is incomplete
		if (pLocalScene == nullptr || pLocalScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || pLocalScene->mRootNode == nullptr)
		{
			std::cout << "ERROR::ASSIMP::" << localImporter.GetErrorString() << std::endl;
		}

		directory = path.substr(0, path.find_last_of('/'));

		TraverseNode(pLocalScene, pLocalScene->mRootNode);
	}

	void Model::TraverseNode(const aiScene* scene, aiNode* node)
	{
		// load mesh
		for (UINT i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* pLocalMesh = scene->mMeshes[node->mMeshes[i]];
			LoadMesh(scene, pLocalMesh);
		}

		// traverse child node
		for (UINT i = 0; i < node->mNumChildren; ++i)
		{
			TraverseNode(scene, node->mChildren[i]);
		}
	}

	void Model::LoadMesh(const aiScene* scene, aiMesh* mesh)
	{

		//std::vector<int>		G;
		//std::vector<int>		F;
		//G.emplace_back(std::move(F));
		//G.insert(G.end(), F.begin(), F.end());
		// process vertex position, normal, tangent, texture coordinates

		/*if(mesh->HasPositions())
		if(mesh->HasNormals())
		if(mesh->HasTangentsAndBitangents())
		if(mesh->HasTextureCoords(0))
		if(mesh->HasVertexColors(0))
		if(mesh->HasFaces())*/

			int nums = mesh->mNumVertices;

			Object::Assimp_Object Object;
			Object.Vertex_Nums = nums;
			Object.VertexCommonStart = *(SceneManager::GetVertexCommonNums());
			Object.Index_Start = *(SceneManager::GetIndexNums());

			Object.Materials .push_back( MatID);

			std::vector<uint32_t> localIndices;

			std::vector<float>			Vertexs;
			std::vector<float>			Normals;
			std::vector<float>			Tangents;
			//std::vector<float>			BaseColor;//该要吗?

			std::vector<std::vector<float>>			UVs;
			UVs.resize(UV_nums);

		for (UINT i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertexs.push_back(mesh->mVertices[i].x);
			Vertexs.push_back(mesh->mVertices[i].y);
			Vertexs.push_back(mesh->mVertices[i].z);

			Normals.push_back(mesh->mNormals[i].x);
			Normals.push_back(mesh->mNormals[i].y);
			Normals.push_back(mesh->mNormals[i].z);

			Tangents.push_back(mesh->mTangents[i].x);
			Tangents.push_back(mesh->mTangents[i].x);
			Tangents.push_back(mesh->mTangents[i].x);
			// assimp allow one model have 8 different texture coordinates in one vertex, but we just care first texture coordinates because we will not use so many
			int num = UV_nums;
			assert ( num > 8);
			for (int i = 0; i < UV_nums; i++)
			{
				UVs[i].push_back(mesh->mTextureCoords[i]->x);
				UVs[i].push_back(mesh->mTextureCoords[i]->y);
				
			}
		}

		for (UINT i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace localFace = mesh->mFaces[i];
			for (UINT j = 0; j < localFace.mNumIndices; ++j)
			{
				localIndices.push_back(localFace.mIndices[j]);
			}
		}

		Object.Index_Length = localIndices.size();
		
		*SceneManager::GetVertexCommonNums()	+=	Vertexs.size();
		*SceneManager::GetIndexNums()			+=	localIndices.size();
		//			放入SceneManager中
		SceneManager::GetVAS()->at(Object::Vertex_Attribute::Position).emplace_back(std::move(Vertexs));
		SceneManager::GetVAS()->at(Object::Vertex_Attribute::Normal).emplace_back(std::move(Normals));
		SceneManager::GetVAS()->at(Object::Vertex_Attribute::tangent).emplace_back(std::move(Tangents));
		SceneManager::GetIS()->emplace_back(std::move(localIndices));

		for (int i = 0; i < UV_nums; i++)
		{
			if (i == 0)
				Object.Vertex_2DTex.UV0_Start = *(SceneManager::GetUV0_Nums());
				*(SceneManager::GetUV0_Nums()) += UVs[0].size();
				SceneManager::GetVAS()->at(Object::Vertex_Attribute::UV0).emplace_back(std::move(UVs[0]));
			if (i == 1)
				Object.Vertex_2DTex.UV1_Start = *(SceneManager::GetUV1_Nums());
				*(SceneManager::GetUV1_Nums()) += UVs[1].size();
				SceneManager::GetVAS()->at(Object::Vertex_Attribute::UV1).emplace_back(std::move(UVs[1]));
			if (i == 2)
				Object.Vertex_2DTex.UV2_Start = *(SceneManager::GetUV2_Nums());
				*(SceneManager::GetUV2_Nums()) += UVs[2].size();
				SceneManager::GetVAS()->at(Object::Vertex_Attribute::UV2).emplace_back(std::move(UVs[2]));
			if (i == 3)
				Object.Vertex_2DTex.UV3_Start = *(SceneManager::GetUV3_Nums());
				*(SceneManager::GetUV3_Nums()) += UVs[3].size();
				SceneManager::GetVAS()->at(Object::Vertex_Attribute::UV3).emplace_back(std::move(UVs[3]));
		}
		
		SceneManager::GetObjecs()->push_back(std::move(Object));

	}



}