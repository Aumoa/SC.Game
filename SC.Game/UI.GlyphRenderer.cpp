using namespace SC;
using namespace SC::Game::UI;

using namespace std;

GlyphRenderer::GlyphRenderer( GlyphBuffer* glyphBuffer ) : mGlyphBuffer( glyphBuffer )
{
    mFillBrush = UISystem::mDefaultBlackBrush;
}

#pragma unmanaged

ULONG STDMETHODCALLTYPE GlyphRenderer::AddRef()
{
    return ( ULONG )InterlockedIncrement64( ( volatile LONG64* )&mRefCount );
}

ULONG STDMETHODCALLTYPE GlyphRenderer::Release()
{
    auto r = InterlockedDecrement64( ( volatile LONG64* )&mRefCount );

    if ( r == 0 )
    {
        delete this;
        return 0;
    }
    else
    {
        return ( ULONG )r;
    }
}

HRESULT STDMETHODCALLTYPE GlyphRenderer::QueryInterface( REFIID riid, void** ppvObject )
{
    if ( riid == __uuidof( IUnknown ) )
    {
        *ppvObject = ( IUnknown* )this;
        AddRef();
        return S_OK;
    }
    else if ( riid == __uuidof( IDWriteTextRenderer ) )
    {
        *ppvObject = ( IDWriteTextRenderer* )this;
        AddRef();
        return S_OK;
    }
    else
    {
        return E_NOINTERFACE;
    }
}

#pragma managed
HRESULT STDMETHODCALLTYPE GlyphRenderer::DrawGlyphRun( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_MEASURING_MODE measuringMode, DWRITE_GLYPH_RUN const* glyphRun, DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription, IUnknown* clientDrawingEffect )
{
    if ( glyphRun->glyphCount )
    {
        if ( clientDrawingContext )
        {
            auto& deviceContext = *( CDeviceContext* )clientDrawingContext;

            //
            // 브러시를 선택합니다.
            Brush^ brush = mFillBrush;
            if ( clientDrawingEffect )
            {
                brush = ( ( RichTextColorUnknown* )clientDrawingEffect )->mBrush;
            }

            deviceContext.SetGraphicsRootConstantBufferView( ( UINT )Slot_UI_Brush, brush->mConstantBuffer->GetGPUVirtualAddress() );

            //
            // 렌더 타입을 설정합니다.
            struct
            {
                UINT renderType;
                float opacity;
            } v;
            v.renderType = 0;
            v.opacity = mOpacity;
            deviceContext.SetGraphicsRoot32BitConstants( ( UINT )Slot_UI_RenderType, 2, &v );

            mGlyphBuffer->DrawGlyphRun( &deviceContext, baselineOriginX, baselineOriginY, glyphRun );
        }
        else
        {
            mGlyphBuffer->PushGlyphRun( glyphRun );
        }
    }

    return S_OK;
}

HRESULT STDMETHODCALLTYPE GlyphRenderer::DrawUnderline( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_UNDERLINE const* underline, IUnknown* clientDrawingEffect )
{
    if ( clientDrawingContext )
    {
        auto& deviceContext = *( CDeviceContext* )clientDrawingContext;

        tag_Rect output;

        output.left = baselineOriginX;
        output.top = baselineOriginY + underline->offset - underline->thickness;
        output.width = underline->width;
        output.height = underline->thickness;

        tag_ShaderInfo shaderInfo;
        shaderInfo.output = output;;

        //
        // 브러시를 선택합니다.
        Brush^ brush = mFillBrush;
        if ( clientDrawingEffect )
        {
            brush = ( ( RichTextColorUnknown* )clientDrawingEffect )->mBrush;
        }

        //
        // 렌더 타입을 설정합니다.
        deviceContext.SetGraphicsRoot32BitConstant( ( UINT )Slot_UI_RenderType, 1 );

        D3D12_RANGE range;
        range.Begin = sizeof( tag_ShaderInfo ) * UISystem::mShaderDispatchInfoIndex;
        range.End = range.Begin + sizeof( tag_ShaderInfo ) * 1;

        auto block = ( tag_ShaderInfo* )UISystem::mShaderDispatchInfo->Map();
        memcpy( block + UISystem::mShaderDispatchInfoIndex, &output, sizeof( tag_ShaderInfo ) * 1 );
        UISystem::mShaderDispatchInfo->Unmap( range );

        auto gpuAddr = UISystem::mShaderDispatchInfo->GetGPUVirtualAddress();
        gpuAddr += UISystem::mShaderDispatchInfoIndex * sizeof( tag_ShaderInfo );

        deviceContext.SetGraphicsRootShaderResourceView( Slot_UI_ShaderInfo, gpuAddr );

        // 셰이더 정보 개체의 위치를 넘깁니다.
        UISystem::mShaderDispatchInfoIndex += 1;
    }

    return S_OK;
}

HRESULT STDMETHODCALLTYPE GlyphRenderer::DrawStrikethrough( void* clientDrawingContext, FLOAT baselineOriginX, FLOAT baselineOriginY, DWRITE_STRIKETHROUGH const* strikethrough, IUnknown* clientDrawingEffect )
{
    if ( clientDrawingContext )
    {
        auto& deviceContext = *( CDeviceContext* )clientDrawingContext;

        tag_Rect output;

        output.left = baselineOriginX;
        output.top = baselineOriginY + strikethrough->offset - strikethrough->thickness;
        output.width = strikethrough->width;
        output.height = strikethrough->thickness;

        tag_ShaderInfo shaderInfo;
        shaderInfo.output = output;;

        //
        // 브러시를 선택합니다.
        Brush^ brush = mFillBrush;
        if ( clientDrawingEffect )
        {
            brush = ( ( RichTextColorUnknown* )clientDrawingEffect )->mBrush;
        }

        //
        // 렌더 타입을 설정합니다.
        deviceContext.SetGraphicsRoot32BitConstant( ( UINT )Slot_UI_RenderType, 1 );

        D3D12_RANGE range;
        range.Begin = sizeof( tag_ShaderInfo ) * UISystem::mShaderDispatchInfoIndex;
        range.End = range.Begin + sizeof( tag_ShaderInfo ) * 1;

        auto block = ( tag_ShaderInfo* )UISystem::mShaderDispatchInfo->Map();
        memcpy( block + UISystem::mShaderDispatchInfoIndex, &output, sizeof( tag_ShaderInfo ) * 1 );
        UISystem::mShaderDispatchInfo->Unmap( range );

        auto gpuAddr = UISystem::mShaderDispatchInfo->GetGPUVirtualAddress();
        gpuAddr += UISystem::mShaderDispatchInfoIndex * sizeof( tag_ShaderInfo );

        deviceContext.SetGraphicsRootShaderResourceView( Slot_UI_ShaderInfo, gpuAddr );

        // 셰이더 정보 개체의 위치를 넘깁니다.
        UISystem::mShaderDispatchInfoIndex += 1;
    }

    return S_OK;
}

#pragma unmanaged
HRESULT STDMETHODCALLTYPE GlyphRenderer::DrawInlineObject( void* clientDrawingContext, FLOAT originX, FLOAT originY, IDWriteInlineObject* inlineObject, BOOL isSideways, BOOL isRightToLeft, IUnknown* clientDrawingEffect )
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE GlyphRenderer::IsPixelSnappingDisabled( void* clientDrawingContext, BOOL* isDisabled )
{
    *isDisabled = true;

    return S_OK;
}

HRESULT STDMETHODCALLTYPE GlyphRenderer::GetCurrentTransform( void* clientDrawingContext, DWRITE_MATRIX* transform )
{
    auto dc = ( ID2D1DeviceContext* )clientDrawingContext;
    dc->GetTransform( ( D2D1_MATRIX_3X2_F* )transform );

    return S_OK;
}

HRESULT STDMETHODCALLTYPE GlyphRenderer::GetPixelsPerDip( void* clientDrawingContext, FLOAT* pixelsPerDip )
{
    auto dc = ( ID2D1DeviceContext* )clientDrawingContext;
    FLOAT dpiX, dpiY;
    dc->GetDpi( &dpiX, &dpiY );
    *pixelsPerDip = dpiX / 96.0f;

    return S_OK;
}