//
//  AlgoritmoViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 7/26/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit

class AlgoritmoViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {

    var tableArray = ["Información General","Dijkstra","Bellman Ford","TSP"]
    var imagesArray = ["ig","dijkstra_icono","bellman_icono","tsp_icono"]
    //var segueIdentifiers = ["A1","A2","A3","A4"]
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return tableArray.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell2") as! DirectCellTableView
        cell.d_text.text = tableArray[indexPath.row]
        cell.d_img.image = UIImage(named: imagesArray[indexPath.row])
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let vc = storyboard?.instantiateViewController(withIdentifier: "sb_directed") as? DirectedViewController
        vc?.titulo = tableArray[indexPath.row]
        self.navigationController?.pushViewController(vc!, animated: true)
    }
}
