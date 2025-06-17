module;

#include "nvrhi/utils.h"
#include "nvrhi/validation.h"
#include "nvrhi/nvrhiHLSL.h"
#include "nvrhi/common/resourcebindingmap.h"

#ifdef NVRHI_HAS_D3D11
#include "nvrhi/d3d11.h"
#endif

#ifdef NVRHI_HAS_D3D12
#include "nvrhi/d3d12.h"
#endif

#ifdef NVRHI_HAS_VULKAN
#include "nvrhi/vulkan.h"
#endif

export module nvrhi;

export namespace nvrhi {

	using nvrhi::c_HeaderVersion;
	using nvrhi::c_MaxRenderTargets;
	using nvrhi::c_MaxViewports;
	using nvrhi::c_MaxVertexAttributes;
	using nvrhi::c_MaxBindingLayouts;
	using nvrhi::c_MaxBindlessRegisterSpaces;
	using nvrhi::c_MaxVolatileConstantBuffersPerLayout;
	using nvrhi::c_MaxVolatileConstantBuffers;
	using nvrhi::c_MaxPushConstantSize;
	using nvrhi::c_ConstantBufferOffsetSizeAlignment;
	using nvrhi::AllSubresources;

	using nvrhi::Color;
	using nvrhi::Viewport;
	using nvrhi::Rect;
	using nvrhi::GraphicsAPI;
	using nvrhi::Format;
	using nvrhi::FormatKind;
	using nvrhi::FormatInfo;
	using nvrhi::FormatSupport;
	using nvrhi::HeapType;
	using nvrhi::HeapDesc;
	using nvrhi::IHeap;
	using nvrhi::HeapHandle;
	using nvrhi::MemoryRequirements;
	using nvrhi::TextureDimension;
	using nvrhi::CpuAccessMode;
	using nvrhi::ResourceStates;
	using nvrhi::MipLevel;
	using nvrhi::ArraySlice;
	using nvrhi::SharedResourceFlags;
	using nvrhi::TextureDesc;
	using nvrhi::TextureSlice;
	using nvrhi::TextureSubresourceSet;
	using nvrhi::ITexture;
	using nvrhi::TextureHandle;
	using nvrhi::IStagingTexture;
	using nvrhi::StagingTextureHandle;
	using nvrhi::TiledTextureCoordinate;
	using nvrhi::TiledTextureRegion;
	using nvrhi::TextureTilesMapping;
	using nvrhi::PackedMipDesc;
	using nvrhi::TileShape;
	using nvrhi::SubresourceTiling;
	using nvrhi::SamplerFeedbackFormat;
	using nvrhi::SamplerFeedbackTextureDesc;
	using nvrhi::ISamplerFeedbackTexture;
	using nvrhi::SamplerFeedbackTextureHandle;
	using nvrhi::VertexAttributeDesc;
	using nvrhi::IInputLayout;
	using nvrhi::InputLayoutHandle;
	using nvrhi::BufferDesc;
	using nvrhi::BufferRange;
	using nvrhi::EntireBuffer;
	using nvrhi::IBuffer;
	using nvrhi::BufferHandle;
	using nvrhi::ShaderType;
	using nvrhi::FastGeometryShaderFlags;
	using nvrhi::CustomSemantic;
	using nvrhi::ShaderDesc;
	using nvrhi::ShaderSpecialization;
	using nvrhi::IShader;
	using nvrhi::ShaderHandle;
	using nvrhi::IShaderLibrary;
	using nvrhi::ShaderLibraryHandle;
	using nvrhi::BlendFactor;
	using nvrhi::BlendOp;
	using nvrhi::ColorMask;
	using nvrhi::BlendState;
	using nvrhi::RasterFillMode;
	using nvrhi::RasterCullMode;
	using nvrhi::RasterState;
	using nvrhi::StencilOp;
	using nvrhi::ComparisonFunc;
	using nvrhi::DepthStencilState;
	using nvrhi::ViewportState;
	using nvrhi::SamplerAddressMode;
	using nvrhi::SamplerReductionType;
	using nvrhi::SamplerDesc;
	using nvrhi::ISampler;
	using nvrhi::SamplerHandle;
	using nvrhi::FramebufferAttachment;
	using nvrhi::FramebufferDesc;
	using nvrhi::FramebufferInfo;
	using nvrhi::FramebufferInfoEx;
	using nvrhi::IFramebuffer;
	using nvrhi::FramebufferHandle;
	using nvrhi::ResourceType;
	using nvrhi::BindingLayoutItem;
	using nvrhi::VulkanBindingOffsets;
	using nvrhi::BindingLayoutDesc;
	using nvrhi::BindlessLayoutDesc;
	using nvrhi::IBindingLayout;
	using nvrhi::BindingLayoutHandle;
	using nvrhi::BindingSetItem;
	using nvrhi::BindingSetDesc;
	using nvrhi::IBindingSet;
	using nvrhi::BindingSetHandle;
	using nvrhi::IDescriptorTable;
	using nvrhi::DescriptorTableHandle;
	using nvrhi::PrimitiveType;
	using nvrhi::SinglePassStereoState;
	using nvrhi::RenderState;
	using nvrhi::VariableShadingRate;
	using nvrhi::ShadingRateCombiner;
	using nvrhi::VariableRateShadingState;
	using nvrhi::BindingLayoutVector;
	using nvrhi::GraphicsPipelineDesc;
	using nvrhi::IGraphicsPipeline;
	using nvrhi::GraphicsPipelineHandle;
	using nvrhi::ComputePipelineDesc;
	using nvrhi::IComputePipeline;
	using nvrhi::ComputePipelineHandle;
	using nvrhi::MeshletPipelineDesc;
	using nvrhi::IMeshletPipeline;
	using nvrhi::MeshletPipelineHandle;
	using nvrhi::IEventQuery;
	using nvrhi::EventQueryHandle;
	using nvrhi::ITimerQuery;
	using nvrhi::TimerQueryHandle;
	using nvrhi::VertexBufferBinding;
	using nvrhi::IndexBufferBinding;
	using nvrhi::BindingSetVector;
	using nvrhi::GraphicsState;
	using nvrhi::DrawArguments;
	using nvrhi::DrawIndirectArguments;
	using nvrhi::DrawIndexedIndirectArguments;
	using nvrhi::ComputeState;
	using nvrhi::DispatchIndirectArguments;
	using nvrhi::MeshletState;
	using nvrhi::Feature;
	using nvrhi::MessageSeverity;
	using nvrhi::CommandQueue;
	using nvrhi::VariableRateShadingFeatureInfo;
	using nvrhi::WaveLaneCountMinMaxFeatureInfo;
	using nvrhi::IMessageCallback;
	using nvrhi::CommandListParameters;
	using nvrhi::ICommandList;
	using nvrhi::CommandListHandle;
	using nvrhi::IDevice;
	using nvrhi::DeviceHandle;

	using nvrhi::verifyHeaderVersion;
	using nvrhi::getFormatInfo;
	using nvrhi::hash_combine;

	using nvrhi::operator&;
	using nvrhi::operator|;
	using nvrhi::operator~;
	using nvrhi::operator!;
	using nvrhi::operator==;
	using nvrhi::operator!=;

	namespace rt {

		using rt::c_IdentityTransform;

		using rt::OpacityMicromapFormat;
		using rt::OpacityMicromapBuildFlags;
		using rt::OpacityMicromapUsageCount;
		using rt::OpacityMicromapDesc;
		using rt::IOpacityMicromap;
		using rt::OpacityMicromapHandle;
		using rt::AffineTransform;
		using rt::GeometryFlags;
		using rt::GeometryType;
		using rt::GeometryAABB;
		using rt::GeometryTriangles;
		using rt::GeometryAABBs;
		using rt::GeometrySpheres;
		using rt::GeometryLssPrimitiveFormat;
		using rt::GeometryLssEndcapMode;
		using rt::GeometryLss;
		using rt::GeometryDesc;
		using rt::InstanceFlags;
		using rt::InstanceDesc;
		using rt::AccelStructBuildFlags;
		using rt::AccelStructDesc;
		using rt::IAccelStruct;
		using rt::AccelStructHandle;
		using rt::PipelineShaderDesc;
		using rt::PipelineHitGroupDesc;
		using rt::PipelineDesc;
		using rt::IShaderTable;
		using rt::ShaderTableHandle;
		using rt::IPipeline;
		using rt::PipelineHandle;
		using rt::State;
		using rt::DispatchRaysArguments;

		using rt::operator&;
		using rt::operator|;
		using rt::operator~;
		using rt::operator!;
		using rt::operator==;
		using rt::operator!=;

		namespace cluster {

			using cluster::OperationType;
			using cluster::OperationMoveType;
			using cluster::OperationMode;
			using cluster::OperationFlags;
			using cluster::OperationIndexFormat;
			using cluster::OperationSizeInfo;
			using cluster::OperationMoveParams;
			using cluster::OperationClasBuildParams;
			using cluster::OperationBlasBuildParams;
			using cluster::OperationParams;
			using cluster::OperationDesc;

			using cluster::operator&;
			using cluster::operator|;
			using cluster::operator~;
			using cluster::operator!;
			using cluster::operator==;
			using cluster::operator!=;
		}
	}

	namespace utils {

		using utils::BitSetAllocator;
		using utils::ScopedMarker;

		using utils::CreateAddBlendState;
		using utils::CreateStaticConstantBufferDesc;
		using utils::CreateVolatileConstantBufferDesc;
		using utils::CreateBindingSetAndLayout;
		using utils::ClearColorAttachment;
		using utils::ClearDepthStencilAttachment;
		using utils::BuildBottomLevelAccelStruct;
		using utils::TextureUavBarrier;
		using utils::BufferUavBarrier;
		using utils::ChooseFormat;
		using utils::GraphicsAPIToString;
		using utils::TextureDimensionToString;
		using utils::DebugNameToString;
		using utils::ShaderStageToString;
		using utils::ResourceTypeToString;
		using utils::FormatToString;
		using utils::CommandQueueToString;
		using utils::GenerateHeapDebugName;
		using utils::GenerateTextureDebugName;
		using utils::GenerateBufferDebugName;
		using utils::NotImplemented;
		using utils::NotSupported;
		using utils::InvalidEnum;
	}

	// resource.h
	using nvrhi::ObjectType;

	namespace ObjectTypes {

		using ObjectTypes::SharedHandle;
#ifdef NVRHI_HAS_D3D11
		using ObjectTypes::D3D11_Device;
		using ObjectTypes::D3D11_DeviceContext;
		using ObjectTypes::D3D11_Resource;
		using ObjectTypes::D3D11_Buffer;
		using ObjectTypes::D3D11_RenderTargetView;
		using ObjectTypes::D3D11_DepthStencilView;
		using ObjectTypes::D3D11_ShaderResourceView;
		using ObjectTypes::D3D11_UnorderedAccessView;
#endif // NVRHI_HAS_D2D11
#ifdef NVRHI_HAS_D3D12
		using ObjectTypes::D3D12_Device;
		using ObjectTypes::D3D12_CommandQueue;
		using ObjectTypes::D3D12_GraphicsCommandList;
		using ObjectTypes::D3D12_Resource;
		using ObjectTypes::D3D12_RenderTargetViewDescriptor;
		using ObjectTypes::D3D12_DepthStencilViewDescriptor;
		using ObjectTypes::D3D12_ShaderResourceViewGpuDescripror;
		using ObjectTypes::D3D12_UnorderedAccessViewGpuDescripror;
		using ObjectTypes::D3D12_RootSignature;
		using ObjectTypes::D3D12_PipelineState;
		using ObjectTypes::D3D12_CommandAllocator;
#endif // NVRHI_HAS_D2D12
#ifdef NVRHI_HAS_VULKAN
		using ObjectTypes::VK_Device;
		using ObjectTypes::VK_PhysicalDevice;
		using ObjectTypes::VK_Instance;
		using ObjectTypes::VK_Queue;
		using ObjectTypes::VK_CommandBuffer;
		using ObjectTypes::VK_DeviceMemory;
		using ObjectTypes::VK_Buffer;
		using ObjectTypes::VK_Image;
		using ObjectTypes::VK_ImageView;
		using ObjectTypes::VK_AccelerationStructureKHR;
		using ObjectTypes::VK_Sampler;
		using ObjectTypes::VK_ShaderModule;
		using ObjectTypes::VK_RenderPass;
		using ObjectTypes::VK_Framebuffer;
		using ObjectTypes::VK_DescriptorPool;
		using ObjectTypes::VK_DescriptorSetLayout;
		using ObjectTypes::VK_DescriptorSet;
		using ObjectTypes::VK_PipelineLayout;
		using ObjectTypes::VK_Pipeline;
		using ObjectTypes::VK_Micromap;
		using ObjectTypes::VK_ImageCreateInfo;
#endif // NVRHI_HAS_VULKAN
	}

	using nvrhi::Object;
	using nvrhi::IResource;
	using nvrhi::RefCountPtr;
	using nvrhi::ResourceHandle;
	using nvrhi::RefCounter;

	// validation.h
	namespace validation {

		using validation::createValidationLayer;
	}

	// nvrhiHLSL.h
	using nvrhi::GpuVirtualAddress;
	using nvrhi::GpuVirtualAddressAndStride;
	
	namespace rt {
		using rt::IndirectInstanceDesc;
		
		namespace cluster {

			using cluster::kClasByteAlignment;
			using cluster::kClasMaxTriangles;
			using cluster::kClasMaxVertices;
			using cluster::kMaxGeometryIndex;

			using cluster::IndirectTriangleClasArgs;
			using cluster::IndirectTriangleTemplateArgs;
			using cluster::IndirectInstantiateTemplateArgs;
			using cluster::IndirectArgs;
		}
	}

	// d3d11.h
#ifdef NVRHI_HAS_D3D11
	namespace ObjectTypes {

		using ObjectTypes::Nvrhi_D3D11_Device;
	}

	namespace d3d11 {

		using d3d11::DeviceDesc;

		using d3d11::createDevice;
		using d3d11::convertFormat;
	}
#endif // NVRHI_HAS_D2D11

	// d2d12.h
#ifdef NVRHI_HAS_D3D12
	namespace ObjectTypes {

		using ObjectTypes::Nvrhi_D3D12_Device;
		using ObjectTypes::Nvrhi_D3D12_CommandList;
	}

	namespace d3d12 {
		using d3d12::IRootSignature;
		using d3d12::RootSignatureHandle;
		using d3d12::ICommandList;
		using d3d12::CommandListHandle;
		using d3d12::DescriptorIndex;
		using d3d12::IDescriptorHeap;
		using d3d12::DescriptorHeapType;
		using d3d12::IDevice;
		using d3d12::DeviceHandle;
		using d3d12::DeviceDesc;

		using d3d12::createDevice;
		using d3d12::convertFormat;
	}
#endif // NVRHI_HAS_D2D12

	// vulkan.h
#ifdef NVRHI_HAS_VULKAN
	namespace ObjectTypes {

		using ObjectTypes::Nvrhi_VK_Device;
	}

	namespace vulkan {

		using vulkan::IDevice; 
		using vulkan::DeviceHandle;
		using vulkan::DeviceDesc;

		using vulkan::createDevice;
		using vulkan::convertFormat;
		using vulkan::resultToString;
	}
#endif // NVRHI_HAS_VULKAN
}

export namespace std {

	template<typename T> struct hash<nvrhi::RefCountPtr<T>>;
	template<> struct hash<nvrhi::TextureSubresourceSet>;
	template<> struct hash<nvrhi::BufferRange>;
	template<> struct hash<nvrhi::BindingSetItem>;
	template<> struct hash<nvrhi::BindingSetDesc>;
	template<> struct hash<nvrhi::FramebufferInfo>;
	template<> struct hash<nvrhi::BlendState::RenderTarget>;
	template<> struct hash<nvrhi::BlendState>;

	// resourcebindingmap.h
	template<> struct hash<nvrhi::TextureBindingKey>;
	template<> struct hash<nvrhi::BufferBindingKey>;
}