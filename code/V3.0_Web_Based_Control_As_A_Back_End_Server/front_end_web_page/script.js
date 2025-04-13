function greetUser() {
    alert("Welcome to MyDeals!");
  }
  
  function sendProduct(productID) {
    console.log("Sending product ID:", productID); // Debugging log
    fetch('http://192.168.1.4/select', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({ product: productID })
    })
    .then(response => {
      if (response.ok) {
        return response.text(); // Parse the response
      } else {
        throw new Error("Failed to contact ESP32, status: " + response.status);
      }
    })
    .then(data => {
      console.log('ESP32 says:', data);
      alert('Robot arm added the Product to your Cart');
    })
    .catch(error => {
      console.error('Error:', error);
      alert('Failed to contact ESP32');
    });
  }
  
  //ESP32 acts as an API server. provides the API by exposing an HTTP endpoint like:http://192.168.1.40/select
  //fetch('http://192.168.1.40/select', { method: 'POST', ... }) This is called a REST API — and the /select path is the API endpoint.
  //This front end uses fetch() to call the API