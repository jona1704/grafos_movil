//
//  UserProfileViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 9/20/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit
import FirebaseAuth

class UserProfileViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .blue
        // Do any additional setup after loading the view.
    }
    
    
    @IBAction func logoutBtnTapped(_ sender: Any) {
        do{
            try Auth.auth().signOut()
            let mainVC = UIStoryboard.init(name: "Main", bundle: nil)
            let loginVC = mainVC.instantiateViewController(withIdentifier: "loginController")
            self.view.window?.rootViewController = loginVC
            self.view.window?.makeKeyAndVisible()
        } catch let err{
            print(err)
        }
    }
}
