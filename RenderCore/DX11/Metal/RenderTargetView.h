// Copyright 2015 XLGAMES Inc.
//
// Distributed under the MIT License (See
// accompanying file "LICENSE" or the website
// http://www.opensource.org/licenses/mit-license.php)

#pragma once

#include "DX11.h"
#include "Format.h"
#include "../../../Utility/IntrusivePtr.h"

namespace RenderCore { namespace Metal_DX11
{
    class DeviceContext;

    class SubResourceSlice
    {
    public:
        unsigned _arraySize;
        unsigned _firstArraySlice;
        unsigned _mipMapIndex;
        SubResourceSlice(unsigned arraySize=0, unsigned firstArraySlice=0, unsigned mipMapIndex=0) : _arraySize(arraySize), _firstArraySlice(firstArraySlice), _mipMapIndex(mipMapIndex) {}
    };
    
    class RenderTargetView
    {
    public:
        typedef ID3D::Resource*                 UnderlyingResource;
        RenderTargetView(UnderlyingResource resource, NativeFormat::Enum format = NativeFormat::Unknown, const SubResourceSlice& arraySlice = SubResourceSlice());
        RenderTargetView(ID3D::RenderTargetView* resource);
        RenderTargetView(MovePTRHelper<ID3D::RenderTargetView> resource);
        RenderTargetView(DeviceContext& context);
        RenderTargetView();
        ~RenderTargetView();

        RenderTargetView(const RenderTargetView& cloneFrom);
        RenderTargetView(RenderTargetView&& moveFrom) never_throws;
        RenderTargetView& operator=(const RenderTargetView& cloneFrom);
        RenderTargetView& operator=(RenderTargetView&& moveFrom) never_throws;
        
        typedef ID3D::RenderTargetView*         UnderlyingType;
        UnderlyingType                          GetUnderlying() const { return _underlying.get(); }
        bool                                    IsGood() const { return _underlying.get() != nullptr; }
    private:
        intrusive_ptr<ID3D::RenderTargetView>      _underlying;
    };

    class DepthStencilView
    {
    public:
        typedef ID3D::Resource*                 UnderlyingResource;
        DepthStencilView(UnderlyingResource resource, NativeFormat::Enum format = NativeFormat::Unknown, const SubResourceSlice& arraySlice = SubResourceSlice());
        DepthStencilView(ID3D::DepthStencilView* resource);
        DepthStencilView(MovePTRHelper<ID3D::DepthStencilView> resource);
        DepthStencilView(DeviceContext& context);
        DepthStencilView();
        ~DepthStencilView();

        DepthStencilView(const DepthStencilView& cloneFrom);
        DepthStencilView(DepthStencilView&& moveFrom) never_throws;
        DepthStencilView& operator=(const DepthStencilView& cloneFrom);
        DepthStencilView& operator=(DepthStencilView&& moveFrom) never_throws;
        
        typedef ID3D::DepthStencilView*         UnderlyingType;
        UnderlyingType                          GetUnderlying() const { return _underlying.get(); }
        bool                                    IsGood() const { return _underlying.get() != nullptr; }
    private:
        intrusive_ptr<ID3D::DepthStencilView>      _underlying;
    };

    class UnorderedAccessView
    {
    public:
        struct Flags
        {
            enum Enum
            {
                AttachedCounter = 1<<0
            };
            typedef unsigned BitField;
        };
        typedef ID3D::Resource*                 UnderlyingResource;
        UnorderedAccessView(UnderlyingResource resource, NativeFormat::Enum format = NativeFormat::Unknown, unsigned mipSize = 0, bool appendBuffer = false, bool forceArray = false);
        UnorderedAccessView(UnderlyingResource resource, Flags::BitField field);
        UnorderedAccessView();
        ~UnorderedAccessView();

        UnorderedAccessView(const UnorderedAccessView& cloneFrom);
        UnorderedAccessView(UnorderedAccessView&& moveFrom) never_throws;
        UnorderedAccessView& operator=(const UnorderedAccessView& cloneFrom);
        UnorderedAccessView& operator=(UnorderedAccessView&& moveFrom) never_throws;
        
        typedef ID3D::UnorderedAccessView*      UnderlyingType;
        UnderlyingType                          GetUnderlying() const { return _underlying.get(); }
        bool                                    IsGood() const { return _underlying.get() != nullptr; }
    private:
        intrusive_ptr<ID3D::UnorderedAccessView>   _underlying;
    };


        ////////////////////////////////////////////////////////////////////////////////////////////////

    
}}

