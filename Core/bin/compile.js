// Requirement
const fs = require('fs');
const path = require('path');

// Setup path
const pathTarget = "../src";

// Read all files in src directory
fs.readdirSync(pathTarget).map(itemFile => {
    // Get file path
    const pathFile = path.resolve(path.join(pathTarget, itemFile));
    
    // Load file
    const file = require(pathFile);

    // Make root
    let rootData = [];

    // Map
    file.map(item => {
        if (item.type == "tiles") {
            // Setup
            rootData.push({
                "type": item.type,
                "colider": item.colider,
                "width": item.width,
                "height": item.height,
                "IDTexture": item.IDTexture,
                "tiles": []
            });

            // Map data tiles
            // <Row>
            item.tiles.map((itemRow, indexRow) => {
                // <Column>
                itemRow.map((itemColumn, indexColumn) => {
                    // If not -1
                    if (itemColumn != -1) {
                        // Get tile position
                        let tileY = 0;
                        let tileX = itemColumn;

                        // Looping
                        while (tileX >= item.row) {
                            tileX -= item.row;
                            tileY += 1;
                        }

                        tileY = (tileY > item.row) ? item.row : tileY;
                        tileX = (tileX > item.column) ? item.column : tileX;

                        // Push data
                        rootData[rootData.length - 1].tiles.push({
                            "tileY": tileY,
                            "tileX": tileX,
                            "gridY": indexRow,
                            "gridX": indexColumn
                        });
                    }
                });
            });
        } else {
            // Setup
            rootData.push({
                "type": item.type,
                "x": item.x,
                "y": item.y
            });
        }

        // Make name file
        let nameFileOut = itemFile.split('.');
        nameFileOut = nameFileOut[0] + ".json";

        // Write file
        fs.writeFileSync("../level/" + nameFileOut, JSON.stringify(rootData), {
            encoding: "utf-8"
        });
    });
});