//
//  RegisterViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 9/19/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit
import FirebaseAuth
import FirebaseFirestore

class RegisterViewController: UIViewController {

    @IBOutlet weak var nombreTextField: UITextField!
    @IBOutlet weak var apellidoTextField: UITextField!
    @IBOutlet weak var emailTextField: UITextField!
    @IBOutlet weak var passwordTextField: UITextField!
    @IBOutlet weak var repetirPasswordTextField: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    
    @IBAction func registerBtnTapped(_ sender: Any) {
        let userNombre = nombreTextField.text
        let userApellido = apellidoTextField.text
        let userEmail = emailTextField.text
        let userPass = passwordTextField.text
        let userRPass = repetirPasswordTextField.text
        // Checamos si los campos están vacíos
        if(userNombre!.isEmpty || userApellido!.isEmpty || userEmail!.isEmpty || userPass!.isEmpty || userRPass!.isEmpty){
            desplegarAlerta("Todos los campos se requieren.")
        } else
        // Checamos si Contraseñas coinciden
        if(userPass != userRPass){
            desplegarAlerta("Contraseñas no coinciden.")
        } else
        // Validamos si password es seguro
        if(esPasswordValido(userPass!) == false){
            desplegarAlerta("Asegurse de que el password tiene al menos 8 caracteres, contenga algun caracter especial y un número.")
        } else{
            // Creando una version limpia del nombre y apellido
            let textNombre = userNombre?.trimmingCharacters(in: .whitespacesAndNewlines)
            let textApellido = userApellido?.trimmingCharacters(in: .whitespacesAndNewlines)
            let textEmail = userEmail?.trimmingCharacters(in: .whitespacesAndNewlines)
            let textPassword = userPass?.trimmingCharacters(in: .whitespacesAndNewlines)
            
            // Almacenamos datos
            Auth.auth().createUser(withEmail: textEmail!, password: textPassword!){(result, error) in
                if error != nil{
                    print(error.debugDescription)
                    self.desplegarAlerta("Error de Registro.")
                } else{
                    let db = Firestore.firestore()
                    db.collection("usuarios").addDocument(data: ["nombre":textNombre!, "apellido":textApellido!, "uid":result!.user.uid]){(error) in
                        if error != nil{
                            self.desplegarAlerta("Error al guardar los datos del Usuario.")
                        }
                    }
                    // Desplegamos alerta de confirmación
                    print("Registro Exitoso")
                    let myAlert = UIAlertController(title: "Confirmación", message: "Regstro Exitoso. !Gracias!", preferredStyle: .alert)
                    let okAccion = UIAlertAction(title: "OK", style: .default){ action in
                        self.dismiss(animated: true, completion: nil)
                    }
                    myAlert.addAction(okAccion)
                    self.present(myAlert, animated: true, completion: nil)
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
    
    func esPasswordValido(_ password: String) -> Bool{
        let passTest = NSPredicate(format: "SELF MATCHES %@", "^(?=.*[a-z])(?=.*[$@$#!%*?&])[A-Za-z\\d$@$#!%*?&]{8,}")
        return passTest.evaluate(with: password)
    }
}
