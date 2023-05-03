var commentList = [];
var baseUrl = 'http://18.218.64.106:5001';

var oldJson = "";
var mytoken = "";

fetchRegularly=setInterval(fetchCommentsForArtwork,500);
fetchArtwork(6);

window.addEventListener('beforeunload', function (event) {
    
  });

// Call functions on page exit
window.addEventListener('beforeunload', function (event) {
    staffInterfaceInvisible();
    logoutStaff();
    clearInterval(fetchRegularly); // stop updating comment list

    // event.preventDefault() // these two lines cause a pop-up asking the user if they really want to close the tab
    // event.returnValue = '' // these two lines cause a pop-up asking the user if they really want to close the tab
  });

document.getElementById('submit-comment').addEventListener("click", (e)=> {
    event.preventDefault(); // prevent the enter key from actually inputting a new line in the input box
	addComment();
});


function displayArtInfo(results) {
    artworkList = results["result"];
    document.getElementById("artwork").src.value = artworkList["path"];
    var artworkInfo = artworkList["title"] + "<br>" + artworkList["artist"] + "<br>" + artworkList["year"];
    document.getElementById("artwork-info").innerHTML = artworkInfo;
}

function fetchArtwork(artworkID) {
    fetch(baseUrl + '/artwork/getbyid/' + artworkID, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayArtInfo(json))
        .catch(error => {
            {
                alert("Fetch Art Error: Something went wrong: " + error);
            }
        })
}
// Build output table from comma delimited list
function formatComments(json) {

    var result = '<table class="table table-success table-striped"><tr><th>Username</th><th>Body</th><th>Image Coords</th><th>Rating</th><tr>';
    json.forEach(function(entry, i) {
        result += "<tr><td class='name'>" + entry['name'] + "</td><td class='body'>" + entry['commentText'];
        result += "</td><td class='imgloc'> (" + entry['x'] + "," + entry['y'] + "), w: " + entry['width'] + "</td><td class='rating'>" + entry['rating'];
        // upvote button
        result += "<button type='button' id='upvote-" + entry['ID'] + "' class='btn btn-upvote btn-sm' data-bs-toggle='button' aria-pressed='false' ";
        result += "onclick=\"upvote(this," + entry['ID'] + ")\">↑</button>";
        // downvote button
        result += "<button type='button' id='downvote-" + entry['ID'] + "' class='btn btn-downvote btn-sm' data-bs-toggle='button' aria-pressed='false' ";
        result += "onclick=\"downvote(this," + entry['ID'] + ")\">↓</button></td>";
    });
    result += "</table>";

    return result;
}

function completeUpvote(results){
    if (results["status"]=="success"){
        console.log("success in upvote")
    };
}

function completeDownvote(results){
    if (results["status"]=="success"){
        console.log("success in downvote")
    };
}


function incrementRating(commentID){
    fetch(baseUrl + '/comment/changerating/' + commentID + "/" + "1", {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => completeUpvote(json))
    .catch(error => {
        {
            alert("Increment Error: Something went wrong: " + error);
        }
    })
}

function decrementRating(commentID){
    fetch(baseUrl + '/comment/changerating/' + commentID + "/" + "-1", {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => completeDownvote(json))
    .catch(error => {
        {
            alert("Decrement Error: Something went wrong: " + error);
        }
    })
}

function toggleUpButton(buttonPressed, commentID){
    if (buttonPressed.classList.contains("active")) { // if green after click
        incrementRating(commentID);
      } else { // if gray after click
        decrementRating(commentID);
      }
}


function resetVoteButton(buttonToActOn){
    // turn it gray
    console.log("attempting to reset button with id " + buttonToActOn.id)
    buttonToActOn.classList.remove('active');
}

function toggleDownButton(buttonPressed, commentID){
    if (buttonPressed.classList.contains("active")) { // if red after click
        decrementRating(commentID);
      } else { // if gray after click
        incrementRating(commentID);
      }
}


function upvote(buttonPressed, commentID){
    console.log("upvoting comment with ID = " + commentID);
    // turn button green or gray, whichever one it wasn't before
    toggleUpButton(buttonPressed, commentID);
    // reset downvote button, which has an element id based on the ID of the comment these buttons apply to
    resetVoteButton(document.getElementById("downvote-" + commentID));
}

function downvote(buttonPressed, commentID){
    console.log("downvoting comment with ID = " + commentID);
    // turn button green or gray, whichever one it wasn't before
    toggleDownButton(buttonPressed, commentID);
    // reset downvote button, which has an element id based on the ID of the comment these buttons apply to
    resetVoteButton(document.getElementById("upvote-" + commentID));
}

function displayComments(isJsonDiff, results) {
    if (isJsonDiff){
        commentList = results["results"];
        console.log("remaking table of comments");
        document.getElementById("searchresults").innerHTML = formatComments(commentList);
    }
}

function isJsonDifferent(newJson){
    if (JSON.stringify(oldJson)===JSON.stringify(newJson)){
        return false;
    } else {
        oldJson = newJson; // update saved json
        return true;
    }
}

function fetchCommentsForArtwork() {
	// Temp Values
    var artworkID = "0";
    var sortParam;
    sortParam = getSortMethod();
	
    fetch(baseUrl + '/comment/fetchforwork/' + artworkID + "/" + sortParam, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayComments(isJsonDifferent(json),json))
        .catch(error => {
            {
                alert("Fetch Comment Error: Something went wrong: " + error);
            }
        })
}

function getSortMethod() {
    const sortMethods = document.querySelectorAll('input[name="sortbtns"]');
    var resultMethod = null;
    sortMethods.forEach((button) => {
        if (button.checked) {
            resultMethod = button.value;
        }
    });
    return resultMethod
}

/* Add contact functions */
function processAdd(results) {
    console.log("Add:", results["status"]);
    document.getElementById("addname").value = "";
    document.getElementById("addbody").value = "";

}

function addComment() {
	// Temp Values
	x = "1"
	y = "1"
	width = "100"
	
    console.log("Attempting to add an entry");
    console.log("Name:" + $('#addname').val());
    fetch(baseUrl + '/comment/add/' + $('#addname').val() + "/" + $('#addbody').val() + "/" + "0" + "/" + x +"/" + y + "/" + width, {
            method: 'get'
            // to do: put artwork id in the place of "0" above
        })
        .then(response => response.json())
        .then(json => processAdd(json))
        .catch(error => {
            {
                alert("Add Error: Something went wrong: " + error);
            }
        })
}

// Staff login event listeners
document.getElementById('login-go').addEventListener("click", loginStaff);
document.getElementById('StaffPW').addEventListener("keydown", (e)=> {
    if (e.code == "Enter") {
        event.preventDefault(); // prevent the enter key from actually inputting a new line in the input box
        console.log("Login enter detected");
        loginStaff();
    }
});
document.getElementById('logout-button').addEventListener("click", logoutStaff);

function staffInterfaceInvisible(){
    console.log("staffInterfaceInvisible() called");
    document.getElementById('login-button').style.display = 'block';
    
    var staffStuff = document.getElementsByClassName('staff-stuff');
    for (var i = 0; i < staffStuff.length; i ++) {
        staffStuff[i].style.display = 'none';
    }

}

function staffInterfaceVisible(){
    console.log("staffInterfaceVisible() called");
    document.getElementById('login-button').style.display = 'none';

    var staffStuff = document.getElementsByClassName('staff-stuff');
    for (var i = 0; i < staffStuff.length; i ++) {
        staffStuff[i].style.display = 'block';
    }


}


function processLogin(results){
    if (results["status"]=="success"){
        // close login modal
        const clickEvent = new MouseEvent('click');
        document.getElementById('login-close').dispatchEvent(clickEvent);

        mytoken = results['token'];

        console.log("login successful")

        staffInterfaceVisible();
    } else {
        alert(results["status"]);
    }
}

function loginStaff(){
    console.log("loginStaff() called");
    fetch(baseUrl + '/stafflogin/' + $('#StaffPW').val(), {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => processLogin(json))
    .catch(error => {
        {
            alert("Login Error: Something went wrong in loginStaff(): " + error);
        }
    })
}

function processLogout(results){
    if (results["status"]=="success"){
        console.log("logout successful")

        staffInterfaceInvisible();
    } else {
        alert(results["status"]);
    }
}

function logoutStaff(){
    console.log("logoutStaff() called");
    fetch(baseUrl + '/stafflogout/' + mytoken, {
        method: 'get'
    })
    .then(response => response.json())
    .then(json => processLogout(json))
    .catch(error => {
        {
            alert("Logout Error: Something went wrong in logoutStaff(): " + error);
        }
    })
}

