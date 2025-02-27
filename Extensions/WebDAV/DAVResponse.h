#import "EEHTTPResponse.h"

@interface DAVResponse : NSObject <EEHTTPResponse> {
@private
  UInt64 _offset;
  NSMutableDictionary* _headers;
  NSData* _data;
  NSInteger _status;
}
- (id) initWithMethod:(NSString*)method headers:(NSDictionary*)headers bodyData:(NSData*)body resourcePath:(NSString*)resourcePath rootPath:(NSString*)rootPath;
@end
