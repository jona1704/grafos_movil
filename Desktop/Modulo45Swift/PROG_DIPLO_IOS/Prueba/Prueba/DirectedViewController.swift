//
//  NoDirectedViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 8/24/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit
//import GraphLayout

class DirectedViewController: UIViewController {

    
    @IBOutlet weak var lblD: UILabel!
    var titulo = ""
    var alert:UIAlertController!
    
    @IBOutlet weak var scrollView: UIScrollView!
    //var graph: Graph = DataSource.createGraph()
    //var graphView: GraphView!
    
    @IBOutlet weak var btnArchivos: UIButton!
    @IBOutlet weak var btnGuardar: UIButton!
    @IBOutlet weak var btnAyuda: UIButton!
    @IBOutlet weak var btnDescripcion: UIButton!
    @IBOutlet weak var btnArista: UIButton!
    @IBOutlet weak var btnNodo: UIButton!
    @IBOutlet weak var btnExportar: UIButton!
    
    
    @IBAction func btnAction(_ sender: UIButton) {
        switch sender.tag {
        case 0:
            btnArchivos.setImage(UIImage(named: "Archivos_activo"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyuda.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
            alert = UIAlertController(title: "Mensaje", message: "Este boton te lleva al área donde se guardan los screnshots de los grafos dibujados.", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        case 1:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar_activo"), for: .normal)
            btnAyuda.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
            alert = UIAlertController(title: "Mensaje", message: "Guardamos el grafo dibujado sobre el canvas.", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        case 2:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyuda.setImage(UIImage(named: "Ayuda_activo"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
            alert = UIAlertController(title: "Mensaje", message: "Con este boton se muestran las indicaciones de como usar el canvas.", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        case 3:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyuda.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripcion_activo"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
            alert = UIAlertController(title: "Mensaje", message: "Se muestra una breve reseña del algoritmo que estamos usando.", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        case 4:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyuda.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista_activo"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
            alert = UIAlertController(title: "Mensaje", message: "Podemos insertar una arista en el canvas seleccionando el nodo inicial y final.", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        case 5:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyuda.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo_activo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
            alert = UIAlertController(title: "Mensaje", message: "Insertamos Nodos sobre el canvas.", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        case 6:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyuda.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar_activo"), for: .normal)
            alert = UIAlertController(title: "Mensaje", message: "Exportamos como imagen .png el grafo dibujado.", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        default:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyuda.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        lblD.text = titulo
        /*graphView = GraphView()
        graph.applyLayout()
        
        graphView.graph = graph
        graphView.frame = CGRect(origin: CGPoint.zero, size: graphView.calcSize(graph: graph))
        scrollView?.addSubview(graphView)
        scrollView?.contentSize = graphView.bounds.size
        graphView.setNeedsDisplay()*/
        // Do any additional setup after loading the view.
    }
}
