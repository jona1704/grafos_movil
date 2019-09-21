//
//  ControllerGaleriaViewController.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 8/26/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit

class GaleriaViewController: UIViewController, UICollectionViewDataSource, UICollectionViewDelegate {
    
    let items = ["Grafo No Dirigido","Grafo Dirigido","Grafo Petersen","Grafo Regular"]
    let images = ["no_dirigido","dirigidos","grafo_petersen","grafo_regular"]
    
    @IBOutlet weak var collectionView: UICollectionView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
        
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return items.count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        let cell:CollectionViewCell = collectionView.dequeueReusableCell(withReuseIdentifier: "cell", for: indexPath) as! CollectionViewCell
        cell.lbl.text = items[indexPath.item]
        cell.img.image = UIImage(named: images[indexPath.item])
        
        return cell
    }
    
    func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        let imageGraphs:ImgGaleriaViewController = self.storyboard?.instantiateViewController(withIdentifier: "ImgGaleriaViewController") as! ImgGaleriaViewController
        
            imageGraphs.main_img = UIImage(named: images[indexPath.item])
            imageGraphs.main_lbl = items[indexPath.item]
        self.navigationController?.pushViewController(imageGraphs, animated: true)
        //print(indexPath.item)
    }
}
