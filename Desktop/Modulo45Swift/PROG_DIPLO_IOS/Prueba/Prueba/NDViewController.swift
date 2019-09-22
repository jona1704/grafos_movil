//
//  NDViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 8/25/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit

class NDViewController: UIViewController {

    
    @IBOutlet weak var lblND: UILabel!
    //@IBOutlet weak var msgND: UILabel!
    
    @IBOutlet weak var btnArchivos: UIButton!
    @IBOutlet weak var btnGuardar: UIButton!
    @IBOutlet weak var btnAyudar: UIButton!
    @IBOutlet weak var btnDescripcion: UIButton!
    @IBOutlet weak var btnArista: UIButton!
    @IBOutlet weak var btnNodo: UIButton!
    @IBOutlet weak var btnExportar: UIButton!
    
    
    @IBOutlet var msgPopover: UIView!
    
    var titulo = ""
    
    @IBAction func btnClick(_ sender: UIButton) {
        switch sender.tag {
        case 0:
            btnArchivos.setImage(UIImage(named: "Archivos_activo"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyudar.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
        case 1:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar_activo"), for: .normal)
            btnAyudar.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
        case 2:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyudar.setImage(UIImage(named: "Ayuda_activo"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
            self.view.addSubview(msgPopover)
            msgPopover.center = self.view.center
        case 3:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyudar.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripcion_activo"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
        case 4:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyudar.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista_activo"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
        case 5:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyudar.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo_activo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
        case 6:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyudar.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar_activo"), for: .normal)
        default:
            btnArchivos.setImage(UIImage(named: "Archivos"), for: .normal)
            btnGuardar.setImage(UIImage(named: "Guardar"), for: .normal)
            btnAyudar.setImage(UIImage(named: "Ayuda"), for: .normal)
            btnDescripcion.setImage(UIImage(named: "Descripción"), for: .normal)
            btnArista.setImage(UIImage(named: "Insertar_Arista"), for: .normal)
            btnNodo.setImage(UIImage(named: "Insertar_Nodo"), for: .normal)
            btnExportar.setImage(UIImage(named: "Exportar"), for: .normal)
        }
    }
    
    
    @IBAction func removeMsgPopover(_ sender: Any) {
        self.msgPopover.removeFromSuperview()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        lblND.text = titulo
        self.msgPopover.layer.cornerRadius = 10
    }
}
