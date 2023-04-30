var commentList = [];
// const baseUrl = 'C:\Users\4dyla\Programming\ArtGalleryProject\Pages\listView';
var baseUrl = 'http://18.218.64.106:5001';

var oldJson = "";


fetchRegularly=setInterval(fetchCommentsForArtwork,500);

window.addEventListener('beforeunload', function (event) {
    clearInterval(fetchRegularly); // stop updating member list
    // event.preventDefault() // these two lines cause a pop-up asking the user if they really want to close the tab
    // event.returnValue = '' // these two lines cause a pop-up asking the user if they really want to close the tab
  });

document.getElementById('submit-comment').addEventListener("click", (e)=> {
    event.preventDefault(); // prevent the enter key from actually inputting a new line in the input box
	addComment();
});

/* Set up events */
// $(document).ready(function() {
	// Add a click event for the filter button
	// document.querySelector("#filter-btn").addEventListener("click", (e) => {
		// var searchStr = 	document.querySelector("#search").value;
    	// findMatches(searchStr);
	// });

    // $(".dropdown-menu li a").click(function() {
        // var selection = $(this).text();
        // $(this).parents(".btn-group").find('.btn').html(selection + ' <span class="caret"></span>');
    // });

	// findMatches(" ");

// });

/* Search and display contact functions */

// Build output table from comma delimited list
function formatComments(json) {

    var result = '<table class="table table-success table-striped"><tr><th>Username</th><th>Body</th><th>Image Coords</th><th>Rating</th><tr>';
    json.forEach(function(entry, i) {
        result += "<tr><td class='name'>" + entry['name'] + "</td><td class='body'>" + entry['commentText'];
        result += "</td><td class='imgloc'> (" + entry['x'] + "," + entry['y'] + "), w: " + entry['width'] + "</td><td class='rating'>" + entry['rating'];
        // upvote button
        result += "<button type='button' id='upvote-" + entry['ID'] + "' class='btn btn-primary btn-sm' ";
        result += "onclick=\"upvote(this," + entry['ID'] + ")\">↑</button>";
        // downvote button
        result += "<button type='button' id='downvote-" + entry['ID'] + "' class='btn btn-primary btn-sm' ";
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

upvoteColor = "green";
downvoteColor = "red";
noVoteColor = "gray";

function toggleUpButton(buttonPressed){
    // if green, turn gray (could do by running reset on the upvote button)
    if (buttonPressed.style.backgroundColor == upvoteColor) {
        buttonPressed.style.backgroundColor = noVoteColor;
        
        // decrement vote
        fetch(baseUrl + '/comment/changerating/' + commentID + "/" + "-1", {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => completeUpvote(json))
        .catch(error => {
            {
                alert("Upvote Error: Something went wrong: " + error);
            }
        })
    }
    // if gray, turn green
    else if (buttonPressed.style.backgroundColor == noVoteColor) {
        buttonPressed.style.backgroundColor = upvoteColor;

        // increment vote
        fetch(baseUrl + '/comment/changerating/' + commentID + "/" + "1", {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => completeUpvote(json))
        .catch(error => {
            {
                alert("Upvote Error: Something went wrong: " + error);
            }
        })
    } else {
        console.log("Unexpected upvote button color; no vote cast.");
    }
}

function resetVoteButton(buttonToActOn){
    // turn it gray
    buttonToActOn.style.backgroundColor = noVoteColor;
}

function toggleDownButton(buttonPressed){
    // if red, turn gray (could do by running reset on the upvote button)
    if (buttonPressed.style.backgroundColor == downvoteColor) {
        buttonPressed.style.backgroundColor = noVoteColor;

        // increment vote
        fetch(baseUrl + '/comment/changerating/' + commentID + "/" + "1", {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => completeUpvote(json))
        .catch(error => {
            {
                alert("Upvote Error: Something went wrong: " + error);
            }
        })
    }
    // if gray, turn red
    else if (buttonPressed.style.backgroundColor == noVoteColor) {
        buttonPressed.style.backgroundColor = downvoteColor;

        // decrement vote
        fetch(baseUrl + '/comment/changerating/' + commentID + "/" + "-1", {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => completeUpvote(json))
        .catch(error => {
            {
                alert("Upvote Error: Something went wrong: " + error);
            }
        })
    }
}

function upvote(buttonPressed, commentID){
    console.log("upvoting comment with ID = " + commentID);

    // turn button green or gray, whichever one it wasn't before
    toggleUpButton(buttonPressed);
    // reset downvote button, which has an element id based on the ID of the comment these buttons apply to
    resetVoteButton(document.getElementById("downvote-" + commentID));
    

    // start timer for this comment (write over old timer)

    
}

function downvote(buttonPressed, commentID){
    console.log("upvoting comment with ID = " + commentID);

    // turn button green or gray, whichever one it wasn't before
    toggleDownButton(buttonPressed);
    // reset downvote button, which has an element id based on the ID of the comment these buttons apply to
    resetVoteButton(document.getElementById("upvote-" + commentID));
    

    // start timer for this comment (write over old timer)

    
}

function displayComments(isJsonDiff, results) {
    if (isJsonDiff){
        commentList = results["results"];
        // console.log("Results:"+JSON.stringify(commentList));
        console.log("remaking table of comments");
        document.getElementById("searchresults").innerHTML = formatComments(commentList);
    }
}

function isJsonDifferent(newJson){
    if (JSON.stringify(oldJson)===JSON.stringify(newJson)){
        console.log("json not different");
        return false;
    } else {
        console.log("Old JSON:"+JSON.stringify(newJson["results"]));
        console.log("NEW JSON:"+JSON.stringify(oldJson["results"]));
        oldJson = newJson; // update saved json
        console.log("json is different");
        return true;
    }
}

function fetchCommentsForArtwork() {
    // artworkID = $('#artworkID').val();
    // sortParam = $('#sortparam').val()
	// Temp Values
    var artworkID = "0";
    var sortParam = "ID";
	
    // console.log("Attempting to fetch artwork comments");
    // console.log("artworkID: " + artworkID + ", sort param: " + sortParam);
    fetch(baseUrl + '/comment/fetchforwork/' + artworkID + "/" + sortParam, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayComments(isJsonDifferent(json),json))
        .catch(error => {
            {
                alert("Fetch Error: Something went wrong: " + error);
            }
        })
}

/* Add contact functions */
function processAdd(results) {
    console.log("Add:", results["status"]);
    document.getElementById("addname").value = "";
    document.getElementById("addbody").value = "";

    // findMatches(" ");

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


// NOT NEEDED FOR COMMENTS?
// function updateContact() {

	//Get ID in the modal
	// var modal = document.querySelector("#editContact");
	// id = modal.getAttribute("editid");
	
    // console.log("Attempting to edit an entry:"+id); 

    // fetch(baseUrl + '/contact/update/' + id + '/' + document.getElementById("editfirst").value 
    		// + '/' + document.getElementById("editlast").value + '/' + document.getElementById("editphone").value + '/' + document.getElementById("edittype").innerText, {
                // method: 'get'
            // })
        // .then(alert("Record for " + document.getElementById("editfirst").value + ' ' + document.getElementById("editlast").value + " updated"))
        // .catch(error => {
            // {
                // alert("Edit Error: something went wrong:" + error);
            // }
        // });
        
    // findMatches(" ");

// }

// SAVE FOR MODERATION PAGE
// function deleteContact(id) {

    // console.log("Attempting to delete an entry:" + id);
    // fetch(baseUrl + '/contact/delete/' + id, {
            // method: 'get'
        // })
        // .then(alert("Deleted Record: " + id))
        // .catch(error => {
            // {
                // alert("Delete Error: Something went wrong:" + error);
            // }
        // });
     // findMatches(" ");

// }


