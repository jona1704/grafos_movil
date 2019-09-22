//
//  ImgGaleriaViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 8/26/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit

class ImgGaleriaViewController: UIViewController, UITextFieldDelegate {

    
    @IBOutlet weak var imgGal: UIImageView!
    @IBOutlet weak var lblGal: UILabel!
    
    @IBOutlet weak var texto: UITextView!
  
    
    var texto_no_dirigido = "Un grafo no dirigido es aquel en el que todas sus aristas son bidireccionales.\n\nLa relación sobre V es simétrica. Las aristas se representan como pares no ordenados {u,v}, u,v ∈ V y u ≠ v."
    
    var texto_dirigido = "Un grafo dirigido o digrafo es un tipo de grafo en el cual las aristas tienen un sentido definido,​ a diferencia del grafo no dirigido, en el cual las aristas son relaciones simétricas y no apuntan en ningún sentido."
    
    var texto_petersen = "El grafo de Petersen es un grafo que sirve como un útil ejemplo y contraejemplo en la teoría de grafos. Este grafo es nombrado así por Julius Peter Christian Petersen, quien lo publicó en 1898.\n\nCaracterísticas:\n\nEs un grafo regular de grado 3.\nDos vértices adyacentes no tienen vecinos en común, no obstante, no es bipartito, pues existen varios ciclos de longitud impar.\nDos vértices no adyacentes tienen exactamente un vecino en común."
    
    var enlace = "Ver más Información"
    
    var main_img: UIImage!
    var main_lbl: String?!
    
    override func viewDidLoad() {
        
        super.viewDidLoad()
        imgGal.image = main_img
        lblGal.text = main_lbl
        
        if lblGal.text == "Grafo No Dirigido"{
            texto.text = texto_no_dirigido
        } else if lblGal.text == "Grafo Dirigido"{
            texto.text = texto_dirigido
        } else if lblGal.text == "Grafo Petersen"{
            texto.text = texto_petersen
        } else{
            texto.text = "sjsjjsjs"
        }
    }
    
    @IBAction func btnOpcion(_ sender: Any) {
        var urlString:String = ""
        if lblGal.text == "Grafo No Dirigido"{
            urlString = "https://es.wikipedia.org/wiki/Grafo"
        } else if lblGal.text == "Grafo Dirigido"{
            urlString = "https://es.wikipedia.org/wiki/Grafo_dirigido"
        } else if lblGal.text == "Grafo Petersen"{
            urlString = "https://es.wikipedia.org/wiki/Grafo_de_Petersen"
        } else{
            urlString = "https://es.wikipedia.org/wiki/Grafo_regular"
        }
        if let url = URL(string:urlString){
            UIApplication.shared.open(url, options: [:]){
                (resultado) in
                if resultado{
                    self.navigationController?.popViewController(animated: true)
                }
                
            }
        }
    }
}
