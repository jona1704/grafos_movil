//
//  CellTableViewTableViewCell.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 8/25/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit

class CellTableView: UITableViewCell {

    
    @IBOutlet weak var img: UIImageView!
    
    @IBOutlet weak var title: UILabel!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
