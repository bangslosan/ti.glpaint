#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import "RMPaintStep.h"

#define kLuminosity			1.0
#define kSaturation			1.0

@protocol RMCanvasViewDelegate;

@interface RMCanvasView : UIView {
	// The pixel dimensions of the backbuffer
	GLint backingWidth;
	GLint backingHeight;
	
	EAGLContext *context;
	
	// OpenGL names for the renderbuffer and framebuffers used to render to this view
	GLuint viewRenderbuffer, viewFramebuffer;
	
	// OpenGL name for the depth buffer that is attached to viewFramebuffer, if it exists (0 if it does not exist)
	GLuint depthRenderbuffer;
	
	GLuint	brushTexture;
	Boolean needsErase;	
    
    CGFloat brushScale_;
    CGFloat brushPixelStep_;
    UIImage *brush_;
    UIColor *brushColor_;
    __unsafe_unretained id<RMCanvasViewDelegate> delegate_;
}

// Brush dimensions dimensions must be a power of 2.
@property(nonatomic, retain) UIImage* brush;
@property(nonatomic, retain) UIColor* brushColor;
@property(nonatomic) CGFloat brushPixelStep;
@property(nonatomic) CGFloat brushScale;
@property(assign) id<RMCanvasViewDelegate> delegate;

- (void)initialize:(CGRect)frame;
- (void)erase;
- (void)renderLineFromPoint:(CGPoint)start toPoint:(CGPoint)end;

- (GLint)backingWidth;
- (GLint)backingHeight;

@end

@protocol RMCanvasViewDelegate <NSObject>

- (void) canvasView:(RMCanvasView*)canvasView painted:(RMPaintStep*)step;

@end