#import "EEHTTPResponse.h"

@interface HTTPErrorResponse : NSObject <EEHTTPResponse> {
    NSInteger _status;
}

- (id)initWithErrorCode:(int)httpErrorCode;

@end
