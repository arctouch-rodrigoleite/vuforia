/*===============================================================================
 Copyright (c) 2018 PTC Inc. All Rights Reserved.
 
 Vuforia is a trademark of PTC Inc., registered in the United States and other
 countries.
 ===============================================================================*/

#import "ToastView.h"

@interface ToastView ()

@property (strong, nonatomic) IBOutlet UIView *mContentView;
@property (strong, nonatomic) IBOutlet UILabel *mToastMsg;

@end

@implementation ToastView

-(instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    
    if(self && self.subviews.count == 0)
    {
        [self initToastView];
    }
    
    return self;
}

-(instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if(self && self.subviews.count == 0)
    {
        [self initToastView];
    }
    
    return self;
}

-(void)initToastView
{
    self.mContentView = [[[NSBundle mainBundle] loadNibNamed:@"Toast" owner:self options:nil] objectAtIndex:0];
    self.mContentView.frame = self.bounds;
    self.mToastMsg = [self.mContentView viewWithTag:1];
    [self addSubview:self.mContentView];
}

- (void)showToastWithMessage: (NSString *)message
{
    // If duration <= 0 toast will stay until hideToast is called
    [self showAndDismissToastWithMessage:message andDuration:0.0f];
}

- (void)showAndDismissToastWithMessage: (NSString *)message
{
    [self showAndDismissToastWithMessage:message andDuration:10.0f];
}

- (void)showAndDismissToastWithMessage: (NSString *)message andDuration:(float) duration
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.mContentView.layer removeAllAnimations];
        [self.mToastMsg setText:message];
        [self.mContentView setAlpha:0.0f];
        [self.mContentView setHidden:NO];
        
        [UIView animateWithDuration:1.0f animations:^{
            [self.mContentView setAlpha:1.0f];
        } completion:^(BOOL finished){
            if(finished && duration > 0)
            {
                [self hideToastWithDelay:duration];
            }
        }];
    });
}

- (void)hideToastWithDelay:(float)delay
{
    dispatch_async(dispatch_get_main_queue(), ^{
        [UIView animateWithDuration:1.0f delay:delay
                            options: UIViewAnimationOptionCurveEaseInOut
                         animations:^{
                             [self.mContentView setAlpha:0.0f];
                         } completion:^(BOOL finished){
                             if(finished)
                             {
                                 [self.mContentView setHidden:YES];
                             }
                         }];
    });
}

- (void)hideToast
{
    [self hideToastWithDelay:0.0f];
}

@end
