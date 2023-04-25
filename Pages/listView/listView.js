var commentList = [];
// const baseUrl = 'C:\Users\4dyla\Programming\ArtGalleryProject\Pages\listView';
var baseUrl = 'http://18.218.64.106:5001';

fetchRegularly=setInterval(fetchCommentsForArtwork,500);

window.addEventListener('beforeunload', function (event) {
    clearInterval(fetchRegularly); // stop updating member list
    // event.preventDefault() // these two lines cause a pop-up asking the user if they really want to close the tab
    // event.returnValue = '' // these two lines cause a pop-up asking the user if they really want to close the tab
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
        result += "<tr><td class='name'>" + entry['name'] + "</td><td class='body'>" + entry['body'];
        result += "</td><td class='imgloc'>" + entry['imgloc'] + "</td><td class='rating'>" + entry['rating'] + "</td>";
        result += "<button type='button' class='btn btn-primary btn-sm' ";
		// FIX THIS
        result += "onclick=\"upvote(" + "COMMENT" + ")\">↑</button>";
        result += "<button type='button' class='btn btn-primary btn-sm' ";
		// FIX THIS
        result += "onclick=\"downvote(" + "COMMENT" + ")\">↓</button>";
    });
    result += "</table>";

    return result;
}

function displayComments(results) {

    commentList = results["results"];
    console.log("Results:"+JSON.stringify(commentList));
    document.getElementById("searchresults").innerHTML = formatComments(commentList);
    
}

function fetchCommentsForArtwork() {
    // artworkID = $('#artworkID').val();
    // sortParam = $('#sortparam').val()
	// Temp Values
    var artworkID = "0";
    var sortParam = "ID";
	
    console.log("Attempting to fetch artwork comments");
    console.log("artworkID: " + artworkID + ", sort param: " + sortParam);
    fetch(baseUrl + '/comment/fetchforwork/' + artworkID + "/" + sortParam, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayComments(json))
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
	x = 0
	y = 0
	width = 100
	
    console.log("Attempting to add an entry");
    console.log("Name:" + $('#addname').val());
    $('#searchresults').empty();
    fetch(baseUrl + '/comment/add/' + $('#addname').val() + "/" + $('#addbody').val() + "/" + '0' + "/" + x +"/" + y + "/" + width, {
            method: 'get'
            // to do: put artwork id in the place of '0' above
        })
        .then(response => response.json())
        .then(json => processAdd(json))
        .catch(error => {
            {
                alert("Add Error: Something went wrong:" + error);
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


