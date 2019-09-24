//
//  LoginViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 9/11/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit
import FirebaseAuth


class LoginViewController: ViewController {
    
    var window: UIWindow?

    @IBOutlet weak var loginButton: UIButton!
    
    @IBOutlet weak var emailTextField: UITextField!
    
    @IBOutlet weak var passwordTextField: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        loginButton.layer.cornerRadius = 10
    }
    
    @IBAction func logginTapped(_ sender: Any) {
        let userEmail = emailTextField.text!
        let userPassword = passwordTextField.text!
        if(userEmail.isEmpty || userPassword.isEmpty){
            desplegarAlerta("Todos los campos se requieren")
        } else{
            let textEmail = userEmail.trimmingCharacters(in: .whitespacesAndNewlines)
            let textPassword = userPassword.trimmingCharacters(in: .whitespacesAndNewlines)
            Auth.auth().signIn(withEmail: textEmail, password: textPassword){
                (result, error) in
                if error != nil{
                    print(error.debugDescription)
                    self.desplegarAlerta("Error de Validación.")
                } else{
                    let mainVC = UIStoryboard.init(name: "Main", bundle: nil)
                    let welcomeVC = mainVC.instantiateViewController(withIdentifier: "welcomeController")
                    self.view.window?.rootViewController = welcomeVC
                    self.view.window?.makeKeyAndVisible()
                }
            }
        }
    }
    
    func desplegarAlerta(_ userMsg:String){
        let miAlerta = UIAlertController(title: "Alerta", message: userMsg, preferredStyle: .alert)
        let okAction  = UIAlertAction(title: "OK", style: .default, handler: nil)
        miAlerta.addAction(okAction)
        self.present(miAlerta, animated: true, completion: nil)
    }
}
