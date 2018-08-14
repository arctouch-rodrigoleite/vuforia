/*===============================================================================
Copyright (c) 2016-2018 PTC Inc. All Rights Reserved.

Copyright (c) 2012-2015 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.
===============================================================================*/

#import <UIKit/UIKit.h>

#import <Vuforia/UIGLViewProtocol.h>

#import "Texture.h"
#import "SampleApplicationSession.h"
#import "Modelv3d.h"
#import "SampleGLResourceHandler.h"
#import "SampleAppRenderer.h"
#import <Vuforia/DataSet.h>
#import <Vuforia/CameraDevice.h>

#define kNumAugmentationTextures 1


// EAGLView is a subclass of UIView and conforms to the informal protocol
// UIGLViewProtocol
@interface ModelTargetsEAGLView : UIView <UIGLViewProtocol, SampleGLResourceHandler, SampleAppRendererControl> {
@private
    // OpenGL ES context
    EAGLContext *context;
    
    // The OpenGL ES names for the framebuffer and renderbuffers used to render
    // to this view
    GLuint defaultFramebuffer;
    GLuint colorRenderbuffer;
    GLuint depthRenderbuffer;

    // Shader handles
    GLuint shaderProgramID;
    GLint vertexHandle;
    GLint normalHandle;
    GLint textureCoordHandle;
    GLint mvpMatrixHandle;
    GLint mvMatrixHandle;
    GLint normalMatrixHandle;
    GLint lightPositionHandle;
    GLint lightColorHandle;
    GLint texSampler2DHandle;
    GLint objMtlGroupDiffuseColorsHandle;
    
    GLuint planeShaderProgramID;
    GLint planeVertexHandle;
    GLint planeNormalHandle;
    GLint planeTextureCoordHandle;
    GLint planeMvpMatrixHandle;
    GLint planeTexSampler2DHandle;
    GLint planeColorHandle;
    
    float mAmbientLightIntensity;
    
    // Texture used when rendering augmentation
    Texture* augmentationTexture[kNumAugmentationTextures];
    
    // Reference to the dataset to be used for the guide view
    Vuforia::DataSet *mDataset;
    
    Modelv3d * mVikingModel;
    
    SampleAppRenderer * sampleAppRenderer;
}

@property (nonatomic, weak) SampleApplicationSession * vapp;
@property (nonatomic, readwrite) UIInterfaceOrientation mARViewOrientation;

- (id)initWithFrame:(CGRect)frame appSession:(SampleApplicationSession *) app;
- (void)setDatasetForGuideView:(Vuforia::DataSet *)dataset;

- (void)finishOpenGLESCommands;
- (void)freeOpenGLESResources;

- (void) configureVideoBackgroundWithViewWidth:(float)viewWidth andHeight:(float)viewHeight;
- (void) changeOrientation:(UIInterfaceOrientation) ARViewOrientation;
- (void) updateRenderingPrimitives;
@end
