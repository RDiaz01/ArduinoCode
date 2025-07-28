const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <title>ESP32 RF Controller</title>
    </head>
    <!-- <style>
        body {background-color: rgba(128, 128, 128, 0.885);}
        h4 {font-family: Arial; text-align: left; color: white;}
        .card
        {
            max-width: 450px;
            min-width: 100px;
        }
    </style> -->
    <body>
        <p>RF Switch Controller</p>
        <div>Switch Set 1</div>
        <div id ="group0">
        </div><br>

        <div>Switch Set 2</div>
        <div id ="group1">
        </div><br>

        <div>Switch Set 3</div>
        <div id ="group2">
        </div><br>

        <p id="output"></p>

        <script>
            const switches = ['S0','S1','S2','S3','S4','S5','S6','S7','S8'];
            var counter = 0;

            for(let i=0; i<3; i++){
                const group = document.querySelector("#group"+i);
                group.innerHTML = switches.map((sw) => `
                    <input type="radio" name="size${i}" value="${sw}" id="${counter++}">
                    <label for="${sw}">${sw}</label>
                `).join(' ');
            }

            for(let ii =0; ii<3; ii++){
              // add an event listener for the change event
              const radioButtons = document.querySelectorAll(`input[name="size${ii}"]`);
              for(const radioButton of radioButtons){
                  radioButton.addEventListener('change', showSelected);
              } 
            }

            function showSelected(e){
                console.log(e);
                var xhr = new XMLHttpRequest();
                
                if(this.checked){
                    document.querySelector('#output').innerText = `You selected ${this.value}`;
                    xhr.open("GET", `/update?state=${this.id}`);
                    xhr.send();
                }
                
            }
        </script>
    </body>
</html>
)=====";