//
//  ViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 7/26/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {

    var tableArray = ["Grafos Dirigidos","Grafos No Dirigidos","Galeria","Acerca de ..."]
    var imgArray = ["dirigida","no_dirigida","gallery","user-male"]
    var segueIdentifiers = ["A","B","C","D"]
    
    override func viewDidLoad() {
        super.viewDidLoad()

        let newBackButton = UIBarButtonItem(title: "Principal",
                                            style: UIBarButtonItem.Style.plain, target: self, action: Selector(("backAction")))
        navigationController?.navigationBar.topItem?.backBarButtonItem = newBackButton
    }
    
    func backAction() -> Void {
        self.navigationController?.popViewController(animated: true)
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return tableArray.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell:MainTableViewCell = tableView.dequeueReusableCell(withIdentifier: "cell") as! MainTableViewCell
        cell.main_text?.text = tableArray[indexPath.row]
        cell.main_img?.image = UIImage(named: imgArray[indexPath.item])
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        performSegue(withIdentifier: segueIdentifiers[indexPath.row], sender: self)
    }


}

