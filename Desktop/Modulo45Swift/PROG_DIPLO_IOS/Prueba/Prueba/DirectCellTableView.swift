//
//  DirectCellTableView.swift
//  Prueba
//
//  Created by Jonathan Cordoba Luna on 8/27/19.
//  Copyright © 2019 Jonathan Cordoba Luna. All rights reserved.
//

import UIKit

class DirectCellTableView: UITableViewCell {

    @IBOutlet weak var d_img: UIImageView!
    @IBOutlet weak var d_text: UILabel!
    
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
