//
//  AppDelegate.m
//  FleksySample_iOS
//
//  Created by Kosta Eleftheriou on 3/25/13.
//  Copyright (c) 2013 Syntellia. All rights reserved.
//

#import "AppDelegate.h"
#import "FleksyTester.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

  NSString* resourcePath = [NSString stringWithFormat:@"%@/FleksyResources/encrypted/en-US/", [[NSBundle mainBundle] bundlePath]];
  FleksyTester::run(resourcePath.UTF8String);
  
  return YES;
}


@end
