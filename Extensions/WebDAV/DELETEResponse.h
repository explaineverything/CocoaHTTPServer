#import "EEHTTPResponse.h"

@interface DELETEResponse : NSObject <EEHTTPResponse> {
  NSInteger _status;
}
- (id) initWithFilePath:(NSString*)path;
@end
