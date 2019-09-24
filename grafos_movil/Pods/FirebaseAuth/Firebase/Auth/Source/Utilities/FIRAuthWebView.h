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

#import <UIKit/UIKit.h>
<<<<<<< HEAD
#import <WebKit/WebKit.h>
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

NS_ASSUME_NONNULL_BEGIN

/** @class FIRAuthWebView
<<<<<<< HEAD
    @brief A class reponsible for creating a WKWebView for use within Firebase Auth.
=======
    @brief A class reponsible for creating a UIWebview for use within Firebase Auth.
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
 */
@interface FIRAuthWebView : UIView

/** @property webView
 *  @brief The web view.
 */
<<<<<<< HEAD
@property(nonatomic, weak) WKWebView *webView;
=======
@property(nonatomic, weak) UIWebView *webView;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

/** @property spinner
 *  @brief The spinner that indicates web view loading.
 */
@property(nonatomic, weak) UIActivityIndicatorView *spinner;

@end

NS_ASSUME_NONNULL_END