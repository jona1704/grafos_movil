//
//  AlgoritmosNDViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 7/26/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit

class AlgoritmosNDViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    
    var tableArray = ["Información General","DFS","BFS"]
    var imgArray = ["ig","dfs","bfs_icon"]
     //var segueIdentifiers = ["B1","B2","B3"]
    
    
    @IBOutlet weak var tableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
        
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 100
    }
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return tableArray.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell") as! CellTableView
        cell.title.text = tableArray[indexPath.row]
        cell.img.image = UIImage(named: imgArray[indexPath.row])
        //cell.textLabel?.text = tableArray[indexPath.row]
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let vc = storyboard?.instantiateViewController(withIdentifier: "sb_no_directed") as? NDViewController
        vc?.titulo = tableArray[indexPath.row]
        self.navigationController?.pushViewController(vc!, animated: true)
    }
}


