/*
 * Copyright 2017 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "FIRAuthWebView.h"

NS_ASSUME_NONNULL_BEGIN

@implementation FIRAuthWebView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    self.backgroundColor = [UIColor whiteColor];
    [self initializeSubviews];
  }
  return self;
}

/** @fn initializeSubviews
    @brief Initializes the subviews of this view.
 */
- (void)initializeSubviews {
<<<<<<< HEAD
<<<<<<< HEAD
  WKWebView *webView = [self createWebView];
=======
  UIWebView *webView = [self createWebView];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  UIWebView *webView = [self createWebView];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  UIActivityIndicatorView *spinner = [self createSpinner];

  // The order of the following controls z-order.
  [self addSubview:webView];
  [self addSubview:spinner];

  [self layoutSubviews];
  _webView = webView;
  _spinner = spinner;
}

- (void)layoutSubviews {
  CGFloat height = self.bounds.size.height;
  CGFloat width = self.bounds.size.width;
  _webView.frame = CGRectMake(0, 0, width, height);
  _spinner.center = _webView.center;
}

/** @fn createWebView
    @brief Creates a web view to be used by this view.
    @return The newly created web view.
 */
<<<<<<< HEAD
<<<<<<< HEAD
- (WKWebView *)createWebView {
  WKWebView *webView = [[WKWebView alloc] initWithFrame:CGRectZero];
=======
- (UIWebView *)createWebView {
  UIWebView *webView = [[UIWebView alloc] initWithFrame:CGRectZero];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
- (UIWebView *)createWebView {
  UIWebView *webView = [[UIWebView alloc] initWithFrame:CGRectZero];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  // Trickery to make the web view not do weird things (like showing a black background when
  // the prompt in the navigation bar animates changes.)
  webView.opaque = NO;
  webView.backgroundColor = [UIColor clearColor];
  webView.scrollView.opaque = NO;
  webView.scrollView.backgroundColor = [UIColor clearColor];
  webView.scrollView.bounces = NO;
  webView.scrollView.alwaysBounceVertical = NO;
  webView.scrollView.alwaysBounceHorizontal = NO;
  return webView;
}

/** @fn createSpinner
    @brief Creates a spinner to be used by this view.
    @return The newly created spinner.
 */
- (UIActivityIndicatorView *)createSpinner {
<<<<<<< HEAD
<<<<<<< HEAD
  UIActivityIndicatorViewStyle spinnerStyle;
#if defined(TARGET_OS_MACCATALYST)
  if (@available(iOS 13.0, *)) {
    spinnerStyle = UIActivityIndicatorViewStyleMedium;
  } else {
    spinnerStyle = UIActivityIndicatorViewStyleGray;
  }
#else
  spinnerStyle = UIActivityIndicatorViewStyleGray;
#endif
=======
  UIActivityIndicatorViewStyle spinnerStyle = UIActivityIndicatorViewStyleGray;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  UIActivityIndicatorViewStyle spinnerStyle = UIActivityIndicatorViewStyleGray;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  UIActivityIndicatorView *spinner =
      [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:spinnerStyle];
  return spinner;
}

@end

NS_ASSUME_NONNULL_END
